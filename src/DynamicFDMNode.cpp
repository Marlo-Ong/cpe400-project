#include "DynamicFDMNode.h"

void DynamicFDMNode::update(int time) {
    // if (!isBroadcasting && time >= nextDataArrivalTime) {
    //     dataToSend = randomInRange(kMinPacketSize, kMaxPacketSize);
    //     isBroadcasting = true;
    //     scheduleNextArrival(time);
    // }

    // int broadcastingNodes = 0;
    // for (const auto &node : nodes)
    // {
    //     if (node.broadcasting())
    //     {
    //         ++broadcastingNodes;
    //     }
    // }

    // if (broadcastingNodes == 0 || numChannels <= 0)
    // {
    //     for (auto &node : nodes)
    //     {
    //         node.transmit(0);
    //     }
    //     return;
    // }

    // int baseChannels = std::max(1, numChannels / broadcastingNodes);

    // for (auto &node : nodes)
    // {
    //     if (node.broadcasting())
    //     {
    //         node.transmit(baseChannels);
    //     }
    //     else
    //     {
    //         node.transmit(0);
    //     }
    // }
}