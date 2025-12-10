#include "Simulation.h"

#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>

#include "FDMANode.h"

Simulation::Simulation(Config config, Protocol::Type protocol)
    : config(config), protocol(protocol), channels(), cumulativeActiveNodes(0.0) {
    nodes.reserve(config.numNodes);

    channels.reserve(config.numChannels);
    for (int i = 0; i < config.numChannels; i++) {
        channels.push_back(std::make_shared<Channel>());
    }

    switch (protocol) {
        case Protocol::Type::DFDM:
            initializeDFDM();
        break;

        case Protocol::Type::TDMA:
            initializeTDMA();
        break;

        case Protocol::Type::FDMA:
            initializeFDMA();
        break;

        default:
            exit(0);
    }
}

void Simulation::initializeDFDM() {
    int nodeId = 1;
    for (int i = 0; i < config.numNodes; i++) {
        nodes.push_back(std::make_unique<DFDMNode>(nodeId++, channels));
    }
}

void Simulation::initializeTDMA() {
    int nodeId = 1;
    for (int i = 0; i < config.numNodes; i++) {

        nodes.push_back(std::make_unique<TDMANode>(
            nodeId++, 
            channels,
            config.numNodes,
            i
        ));
    }
}

void Simulation::initializeFDMA() {
    int nodeId = 1;
    for (int i = 0; i < config.numNodes; ++i) {
        nodes.push_back(std::make_unique<FDMANode>(nodeId++, channels, config.numNodes));
    }
}

void Simulation::run() {
    for (int t = 0; t < config.simTime; ++t) {
        injectRandomTraffic();
        int activeNodes = 0;
        for (const auto& node : nodes) {
            if (node->getdataToSend() > 0) {
                ++activeNodes;
            }
        }
        cumulativeActiveNodes += activeNodes;
        for (auto& node : nodes) {
            node->update(t);
        }
    }
}

void Simulation::printResults() const {
    std::cout << "=== PROTOCOL: " << Protocol::name(protocol) << " ===\n";

    int totalSent = 0;
    for (const auto& node : nodes) {
        std::cout << "Node " << node->getId() << " sent " << node->getTotalDataSent() << " units\n";
        totalSent += node->getTotalDataSent();
    }

    double throughput = config.simTime > 0 ? static_cast<double>(totalSent) / config.simTime : 0.0;
    std::cout << "\nTotal data sent: " << totalSent << "\n";
    std::cout << "Average throughput: " << throughput << " units/tick\n";

    double channelRate = static_cast<double>(config.numChannels);
    double averageActive = config.simTime > 0 ? cumulativeActiveNodes / config.simTime : 0.0;
    double idealShare = averageActive > 0.0 ? channelRate / averageActive : channelRate;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Channel rate R: " << channelRate << " units/tick\n";
    std::cout << "Average active nodes M: " << averageActive << "\n";
    std::cout << "Ideal per-node throughput R/M: " << idealShare << " units/tick\n\n";

    for (const auto& node : nodes) {
        double nodeThroughput = config.simTime > 0
                                    ? static_cast<double>(node->getTotalDataSent()) / config.simTime
                                    : 0.0;
        double ratioToR = channelRate > 0.0 ? (nodeThroughput / channelRate) * 100.0 : 0.0;
        double ratioToIdeal = idealShare > 0.0 ? (nodeThroughput / idealShare) * 100.0 : 0.0;
        std::cout << "Node " << node->getId() << " avg throughput: " << nodeThroughput
                  << " units/tick (" << ratioToR << "% of R, " << ratioToIdeal
                  << "% of R/M)\n";
    }

    std::cout << "\n";
}

int Simulation::nextArrivalTime(int currentTime) {
    return currentTime + randomInRange(kMinIdleGap, kMaxIdleGap);
}

int Simulation::randomInRange(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator());
}

std::mt19937& Simulation::generator() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

void Simulation::injectRandomTraffic()
{
    if (nodes.empty())
    {
        return;
    }

    std::uniform_real_distribution<double> choiceDist(0.0, 1.0);
    std::uniform_int_distribution<int> payloadDist(15, kMaxPacketSize);
    const double injectionProbability = 0.2;
    
    if (choiceDist(generator()) < injectionProbability)
    {
        return;
    }

    for (auto &node : nodes)
    {
        if (choiceDist(generator()) < injectionProbability)
        {
            node->injectData(payloadDist(generator()));
        }
    }
}
