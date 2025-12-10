#include "TDMANode.h"

void TDMANode::update(int time) {
    if (isAssigned(time)) {
        for(auto channel : channels) {
            if(dataToSend > 0) {
                channel->sendPacket(id);
                totalDataSent++;
                dataToSend--;
            }
        }
    }
}

bool TDMANode::isAssigned(int time) {
    return time % numNodes == assignedTime;
}