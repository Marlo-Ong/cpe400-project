#include "Simulation.h"

#include <iostream>
#include <numeric>
#include <random>

Simulation::Simulation(Config config, Protocol::Type protocol)
    : config(config), protocol(protocol), channels() {
    nodes.reserve(config.numNodes);

    channels.reserve(config.numChannels);
    for (int i = 0; i < config.numChannels; i++) {
        channels.emplace_back();
    }

    switch (protocol) {
        case Protocol::Type::DynamicFDM:
            initializeDynamicFDM();
        break;

        case Protocol::Type::TDMA:
            initializeTDMA();
        break;

        default:
            exit(0);
    }
}

void Simulation::initializeDynamicFDM() {
    int nodeId = 1;
    for (int i = 0; i < config.numNodes; i++) {
        nodes.push_back(std::make_unique<DynamicFDMNode>(nodeId++, channels));
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

void Simulation::run() {
    for (int t = 0; t < config.simTime; ++t) {
        injectRandomTraffic();
        for (auto& node : nodes) {
            node->update(t);
        }
    }
}

void Simulation::printResults() const {
    std::cout << "Protocol: " << Protocol::name(protocol) << "\n";

    int totalSent = 0;
    for (const auto& node : nodes) {
        std::cout << "Node " << node->getId() << " sent " << node->getTotalDataSent() << " units\n";
        totalSent += node->getTotalDataSent();
    }

    double throughput = config.simTime > 0 ? static_cast<double>(totalSent) / config.simTime : 0.0;
    std::cout << "Total data sent: " << totalSent << "\n";
    std::cout << "Average throughput: " << throughput << " units/tick\n\n";
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
