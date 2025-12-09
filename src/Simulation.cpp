#include "Simulation.h"

#include <iostream>
#include <numeric>

Simulation::Simulation(Config config, Protocol::Type protocol)
    : config(config), protocol(protocol) {
    nodes.reserve(config.numNodes);
    for (int i = 0; i < config.numNodes; i++) {
        nodes.push_back(std::move(Protocol::node(protocol)));
    }
    channels.reserve(config.numChannels);
    for (int i = 0; i < config.numChannels; i++) {
        channels.emplace_back();
    }
}

void Simulation::run() {
    for (int t = 0; t < config.simTime; ++t) {
        for (auto& node : nodes) {
            node->update();
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
