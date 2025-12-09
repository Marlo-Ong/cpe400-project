#include "DFDMNode.h"

void DFDMNode::update(int time) {
    if (dataToSend <= 0) {
        vacateChannels();
        return;
    }
    
    //check for available channels
    for (long unsigned int i = 1; i < channels.size(); i++) {
        if (channels[i].readState() == 0) {
            currentChannels.insert(i);
        
        } else if (channels[i].readState() == -1) {
            // if one of the channels we held had a collision, stop using it for now
            currentChannels.erase(i);
        }
    }
    
    if (!currentChannels.empty()) {
        // send data through the currently held channels
        for (auto i : currentChannels) {
            channels[i].writeState(id);
            dataToSend--;
            totalDataSent++;
            if (dataToSend <= 0) {
                vacateChannels();
                break;
            }
        }
    } else {
        // request channels on commumication channel
        channels[0].writeState(id);
    }

    // if another node is requesting channels, free up some of ours
    if (channels[0].readState() != 0) {
        int broadcasting = numBroadcastingNodes();
        // each node should relinquish numChannels / numBroadcasting(numBroadcasting+1) channels
        int release = (channels.size() - 1) / (broadcasting * (broadcasting + 1));
        for (auto i : currentChannels) {
            if (release <= 0 || currentChannels.empty())
                break;
            currentChannels.erase(i);
            release--;
        }
    }
}

void DFDMNode::vacateChannels() {
    for (auto i : currentChannels) {
        channels[i].writeState(0);
    }
    currentChannels.clear();
}

int DFDMNode::numBroadcastingNodes() {
    std::set<int> seenIds;
    int count = 0;

    for (long unsigned int i = 1; i < channels.size(); i++) {
        int state = channels[i].readState();
        if (state > 0) {
            if (seenIds.count(state) == 0) {
                count++;
                seenIds.insert(state);
            }
        }
    }

    return count;
}