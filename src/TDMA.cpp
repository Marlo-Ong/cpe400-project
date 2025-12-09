#include "TDMA.h"

void TDMA::update(std::vector<Node> &nodes, int time, int /*totalChannels*/)
{
    if (nodes.empty())
        return;

    // Only allow the node in the current timeslot to transmit
    int slot = time % nodes.size();
    nodes[slot].transmit(1);
}

std::string TDMA::name() const
{
    return "TDMA";
}
