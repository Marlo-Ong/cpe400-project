#include "FDMANode.h"

FDMANode::FDMANode(int nodeId, std::vector<std::shared_ptr<Channel>> channels, int totalNodes)
    : Node(nodeId, channels) {
    // divide the channels evenly among the nodes
    for (size_t i = 0; i < channels.size(); ++i) {
        if (static_cast<int>((i - 1) % totalNodes) == ((id - 1) % totalNodes)) {
            ownedChannels.push_back(channels[i]);
        }
    }
}

void FDMANode::update(int /*time*/) {
    if (dataToSend <= 0) {
        return;
    }

    for (auto channel : ownedChannels) {
        if (dataToSend <= 0) {
            break;
        }
        channel->sendPacket(id);
        --dataToSend;
        ++totalDataSent;
    }
}
