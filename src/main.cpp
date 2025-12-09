#include <iostream>
#include <stdexcept>

#include "Simulation.h"
#include "Protocol.h"

int parseArg(char* value, int fallback);
Simulation::Config getConfig(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    Simulation::Config config = getConfig(argc, argv);

    std::cout << "Running with " << config.numNodes << " nodes, "
              << config.simTime << " ticks, " << config.numChannels << " channels.\n\n";

    // run simulation with *custom* dynamic frequency-division multiplexing algorithm
    Simulation dynamicSim(config, Protocol::Type::DFDM);
    dynamicSim.run();
    dynamicSim.printResults();

    // run simulation with time-division multiplexing algorithm
    Simulation tdmaSim(config, Protocol::Type::TDMA);
    tdmaSim.run();
    tdmaSim.printResults();

    // run simulation with frequency-division multiplexing algorithm
    Simulation fdmaSim(config, Protocol::Type::FDMA);
    fdmaSim.run();
    fdmaSim.printResults();

    std::cout << "Simulation complete.\n";
    return 0;
}

Simulation::Config getConfig(int argc, char* argv[]) {
    int numNodes = 10;
    int simTime = 1000;
    int numChannels = 50;

    if (argc > 1) {
        numNodes = parseArg(argv[1], numNodes);
    }
    if (argc > 2) {
        simTime = parseArg(argv[2], simTime);
    }
    if (argc > 3) {
        numChannels = parseArg(argv[3], numChannels);
    }

    return {numNodes = numNodes, simTime = simTime, numChannels = numChannels};
}

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
