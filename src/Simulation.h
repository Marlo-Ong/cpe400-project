#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "Channel.h"
#include "Node.h"
#include "Protocol.h"

struct Config
{
    int numNodes;
    int simTime;
    int totalChannels;
};

// Runs the given protocol using the configurable data
class Simulation
{
public:
    Simulation(Config config, Protocol &protocol);

    void run();
    void printResults() const;

private:
    Config config;
    Protocol &protocol;
    std::vector<Node> nodes;
    std::vector<Channel> channels;
};

#endif
