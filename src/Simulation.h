#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "Node.h"
#include "Protocol.h"

class Simulation {
public:
    Simulation(int numNodes, int simTime, int totalChannels, Protocol& protocol);

    void run();
    void printResults() const;

private:
    int numNodes;
    int simTime;
    int totalChannels;
    Protocol& protocol;
    std::vector<Node> nodes;
};

#endif
