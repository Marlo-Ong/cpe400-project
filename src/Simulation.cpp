#include "Simulation.h"

#include <iostream>
#include <numeric>

Simulation::Simulation(int nodeCount, int duration, int channels, Protocol& proto)
    : numNodes(nodeCount),
      simTime(duration),
      totalChannels(channels),
      protocol(proto) {
    nodes.reserve(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        nodes.emplace_back(i);
    }
}

void Simulation::run() {
    for (int t = 0; t < simTime; ++t) {
        for (auto& node : nodes) {
            node.update(t);
        }
        protocol.update(nodes, t, totalChannels);
    }
}

void Simulation::printResults() const {
    std::cout << "Protocol: " << protocol.name() << "\n";

    int totalSent = 0;
    for (const auto& node : nodes) {
        std::cout << "Node " << node.getId() << " sent " << node.getTotalDataSent() << " units\n";
        totalSent += node.getTotalDataSent();
    }

    double throughput = simTime > 0 ? static_cast<double>(totalSent) / simTime : 0.0;
    std::cout << "Total data sent: " << totalSent << "\n";
    std::cout << "Average throughput: " << throughput << " units/tick\n\n";
}
