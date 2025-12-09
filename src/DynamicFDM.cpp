#include "DynamicFDM.h"

#include <algorithm>

// DynamicFDM splits spectrum evenly among all currently broadcasting nodes.
void DynamicFDM::update(std::vector<Node> &nodes, std::vector<Channel> &channels, int /*time*/)
{
    std::vector<int> activeIndices;
    activeIndices.reserve(nodes.size());
    for (int i = 0; i < static_cast<int>(nodes.size()); ++i)
    {
        if (nodes[i].broadcasting())
        {
            activeIndices.push_back(i);
        }
    }

    if (activeIndices.empty())
    {
        return;
    }

    // Assign each physical channel to a broadcasting node in round-robin fashion.
    for (auto &channel : channels)
    {
        int ownerIndex = activeIndices[channel.id() % static_cast<int>(activeIndices.size())];
        channel.assign(nodes[ownerIndex].getId());
        nodes[ownerIndex].addChannel(channel.id());
    }
}

std::string DynamicFDM::name() const
{
    // Label used when printing results.
    return "Dynamic-FDM";
}
