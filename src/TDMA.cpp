#include "TDMA.h"

void TDMA::update(std::vector<Node>& nodes, int time, int /*totalChannels*/) {
    if (nodes.empty()) {
        return;
    }

    int activeIndex = time % static_cast<int>(nodes.size());
    for (int i = 0; i < static_cast<int>(nodes.size()); ++i) {
        if (i == activeIndex) {
            nodes[i].transmit(1);
        } else {
            nodes[i].transmit(0);
        }
    }
}

std::string TDMA::name() const {
    return "TDMA";
}
