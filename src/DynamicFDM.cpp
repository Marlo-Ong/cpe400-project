#include "DynamicFDM.h"

#include <algorithm>

void DynamicFDM::update(std::vector<Node> &nodes, int /*time*/, int totalChannels)
{
    // Count the number of nodes currently broadcasting
    int broadcastingNodes = 0;
    for (const auto &node : nodes)
    {
        if (node.broadcasting())
        {
            ++broadcastingNodes;
        }
    }

    // No one is broadcasting
    if (broadcastingNodes == 0 || totalChannels <= 0)
    {
        for (auto &node : nodes)
        {
            node.transmit(0);
        }
        return;
    }

    // Split among remaining channels
    int numChannels = std::max(1, totalChannels / broadcastingNodes);

    for (auto &node : nodes)
    {
        if (node.broadcasting())
        {
            // Active nodes all get the same share of channels
            node.transmit(numChannels);
        }
        else
        {
            node.transmit(0);
        }
    }
}

std::string DynamicFDM::name() const
{
    // Label used when printing results.
    return "Dynamic-FDM";
}
