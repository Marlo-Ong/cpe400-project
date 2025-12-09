#include "TDMANode.h"
#include <iostream>

void TDMANode::update(int time) {
    if (isAssigned(time)) {
        for(auto channel : *channels) {
            channel.writeState(id);
            totalDataSent++;
        }
        std::cout << "Node " << id << " sent data. Total sent: " << totalDataSent << "." << std::endl;

    }
    // if (!isBroadcasting && time >= nextDataArrivalTime) {
    //     remainingData = randomInRange(kMinPacketSize, kMaxPacketSize);
    //     isBroadcasting = true;
    //     scheduleNextArrival(time);
    // }

    // if (nodes.empty()) {
    //     return;
    // }

    // int activeIndex = time % static_cast<int>(nodes.size());
    // for (int i = 0; i < static_cast<int>(nodes.size()); ++i) {
    //     if (i == activeIndex) {
    //         nodes[i].transmit(1);
    //     } else {
    //         nodes[i].transmit(0);
    //     }
    // }

}

bool TDMANode::isAssigned(int time) {
    return time % numNodes == assignedTime;
}