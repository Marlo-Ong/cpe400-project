#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <random>

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

    void initializeDynamicFDM();
    void initializeTDMA();
    void injectRandomTraffic();

    int nextArrivalTime(int currentTime);
    static int randomInRange(int min, int max);

    static std::mt19937& generator();

    static constexpr int kMinPacketSize = 5;
    static constexpr int kMaxPacketSize = 20;
    static constexpr int kMinIdleGap = 3;
    static constexpr int kMaxIdleGap = 8;
};

#endif
