#include <iostream>
#include <stdexcept>

#include "DynamicFDM.h"
#include "FDMA.h"
#include "Simulation.h"
#include "TDMA.h"

int parseArg(char *value, int fallback);
Config getConfig(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    Config config = getConfig(argc, argv);

    std::cout << "Running with " << config.numNodes << " nodes, "
              << config.simTime << " ticks, " << config.totalChannels << " channels.\n\n";

    // Run simulation with custom dynamic frequency-division multiplexing algorithm
    DynamicFDM dynamicProtocol;
    Simulation dynamicSim(config, dynamicProtocol);
    dynamicSim.run();
    dynamicSim.printResults();

    // Run static frequency-division allocation for comparison
    FDMA fdmaProtocol;
    Simulation fdmaSim(config, fdmaProtocol);
    fdmaSim.run();
    fdmaSim.printResults();

    // run simulation with time-division multiplexing algorithm (TDMA)
    TDMA tdmaProtocol;
    Simulation tdmaSim(config, tdmaProtocol);
    tdmaSim.run();
    tdmaSim.printResults();

    std::cout << "Simulation complete.\n";
    return 0;
}

Config getConfig(int argc, char *argv[])
{
    // (default configuration)
    int numNodes = 6;
    int simTime = 200;
    int totalChannels = 12;

    // parse command line arguments
    if (argc > 1)
    {
        numNodes = parseArg(argv[1], numNodes);
    }
    if (argc > 2)
    {
        simTime = parseArg(argv[2], simTime);
    }
    if (argc > 3)
    {
        totalChannels = parseArg(argv[3], totalChannels);
    }

    return {numNodes = numNodes, simTime = simTime, totalChannels = totalChannels};
}

// stoi with default
int parseArg(char *value, int fallback)
{
    if (!value)
    {
        return fallback;
    }
    try
    {
        int parsed = std::stoi(value);
        return parsed > 0 ? parsed : fallback;
    }
    catch (const std::exception &)
    {
        return fallback;
    }
}
