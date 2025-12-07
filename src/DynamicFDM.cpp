#include "DynamicFDM.h"

#include <algorithm>

void DynamicFDM::update(std::vector<Node> &nodes, int /*time*/, int totalChannels)
{
    int broadcastingNodes = 0;
    for (const auto &node : nodes)
    {
        if (node.broadcasting())
        {
            ++broadcastingNodes;
        }
    }

    if (broadcastingNodes == 0 || totalChannels <= 0)
    {
        for (auto &node : nodes)
        {
            node.transmit(0);
        }
        return;
    }

    int baseChannels = std::max(1, totalChannels / broadcastingNodes);

    for (auto &node : nodes)
    {
        if (node.broadcasting())
        {
            node.transmit(baseChannels);
        }
        else
        {
            node.transmit(0);
        }
    }
}

std::string DynamicFDM::name() const
{
    return "Dynamic-FDM";
}
