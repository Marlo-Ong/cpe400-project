#include "FDMA.h"

void FDMA::update(std::vector<Node> &nodes, std::vector<Channel> &channels, int /*time*/)
{
    if (nodes.empty())
    {
        return;
    }

    for (auto &channel : channels)
    {
        int ownerIndex = channel.id() % static_cast<int>(nodes.size());
        channel.assign(nodes[ownerIndex].getId());
        nodes[ownerIndex].addChannel(channel.id());
    }
}

std::string FDMA::name() const
{
    return "FDMA";
}
