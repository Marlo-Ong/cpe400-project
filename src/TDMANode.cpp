#include "TDMANode.h"

void TDMANode::update(int time) {
    if (isAssigned(time)) {
        for(auto channel : channels) {
            if(dataToSend > 0) {
                channel.writeState(id);
                totalDataSent++;
                dataToSend--;
            }
        }
    }
}

bool TDMANode::isAssigned(int time) {
    return time % numNodes == assignedTime;
}