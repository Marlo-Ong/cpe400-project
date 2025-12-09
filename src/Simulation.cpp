#include "Simulation.h"

#include <iostream>
#include <numeric>

Simulation::Simulation(Config config, Protocol &protocol) : config(config), protocol(protocol)
{
    // Build the node population
    nodes.reserve(config.numNodes);
    for (int i = 0; i < config.numNodes; ++i)
    {
        nodes.emplace_back(i);
    }
}

void Simulation::run()
{
    // main simulation loop
    for (int t = 0; t < config.simTime; ++t)
    {
        for (auto &node : nodes)
        {
            node.update(t);
        }
        protocol.update(nodes, t, config.totalChannels);
    }
}

void Simulation::printResults() const
{
    std::cout << "Protocol: " << protocol.name() << "\n";

    int totalSent = 0;
    for (const auto &node : nodes)
    {
        std::cout << "Node " << node.getId() << " sent " << node.getTotalDataSent() << " units\n";
        totalSent += node.getTotalDataSent();
    }

    double throughput = config.simTime > 0 ? static_cast<double>(totalSent) / config.simTime : 0.0;
    std::cout << "Total data sent: " << totalSent << "\n";
    std::cout << "Average throughput: " << throughput << " units/tick\n\n";
}
