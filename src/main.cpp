#include <iostream>
#include <stdexcept>

#include "DynamicFDM.h"
#include "Simulation.h"
#include "TDMA.h"

namespace {
int parseArg(char* value, int fallback) {
    if (!value) {
        return fallback;
    }
    try {
        int parsed = std::stoi(value);
        return parsed > 0 ? parsed : fallback;
    } catch (const std::exception&) {
        return fallback;
    }
}
}

int main(int argc, char* argv[]) {
    int numNodes = 6;
    int simTime = 200;
    int totalChannels = 12;

    if (argc > 1) {
        numNodes = parseArg(argv[1], numNodes);
    }
    if (argc > 2) {
        simTime = parseArg(argv[2], simTime);
    }
    if (argc > 3) {
        totalChannels = parseArg(argv[3], totalChannels);
    }

    std::cout << "Running with " << numNodes << " nodes, "
              << simTime << " ticks, " << totalChannels << " channels.\n\n";

    DynamicFDM dynamicProtocol;
    Simulation dynamicSim(numNodes, simTime, totalChannels, dynamicProtocol);
    dynamicSim.run();
    dynamicSim.printResults();

    TDMA tdmaProtocol;
    Simulation tdmaSim(numNodes, simTime, totalChannels, tdmaProtocol);
    tdmaSim.run();
    tdmaSim.printResults();

    std::cout << "Simulation complete.\n";
    return 0;
}
