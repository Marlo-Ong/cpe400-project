#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "Protocol.h"
#include "Node.h"
#include "Channel.h"

class Simulation {
public:
    struct Config {
        int numNodes;
        int simTime;
        int numChannels;
    };

    Simulation(Config config, Protocol::Type protocol);

    void run();
    void printResults() const;

private:
    Config config;
    Protocol::Type protocol;
    std::vector<Channel> channels;
    std::vector<std::unique_ptr<Node>> nodes;
};

#endif
