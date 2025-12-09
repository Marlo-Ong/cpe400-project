#include "TDMA.h"

// TDMA allows exactly one node to own a single channel in each time slice.
void TDMA::update(std::vector<Node> &nodes, std::vector<Channel> &channels, int time)
{
    if (nodes.empty() || channels.empty())
        return;

    int slot = time % nodes.size();
    if (!nodes[slot].broadcasting())
        return;

    // Grant the first channel to the scheduled node.
    channels.front().assign(nodes[slot].getId());
    nodes[slot].addChannel(channels.front().id());
}

std::string TDMA::name() const
{
    return "TDMA";
}
