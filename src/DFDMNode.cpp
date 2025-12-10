#include "DFDMNode.h"

void DFDMNode::update(int time) {
    if (dataToSend <= 0) {
        vacateChannels();
        return;
    }
    
    //check for available channels
    for (auto ch : channels) {
        if (ch->readState() == 0) {
            currentChannels.insert(ch);
        
        } else if (ch->readState() == -1) {
            // if one of the channels we held had a collision, stop using it for now
            currentChannels.erase(ch);
        }
    }
    
    if (!currentChannels.empty()) {
        // send data through the currently held channels
        for (auto ch : currentChannels) {
            ch->writeState(id);
            dataToSend--;
            totalDataSent++;
            if (dataToSend <= 0) {
                vacateChannels();
                break;
            }
        }
    } else {
        // request channels on commumication channel
        channels[0]->writeState(id);
    }

    // if another node is requesting channels, free up some of ours
    if (coordChannel->readState() != 0) {
        int broadcasting = numBroadcastingNodes();
        // each node should relinquish C / n(n+1) channels
        int release = (channels.size() - 1) / (broadcasting * (broadcasting + 1));
        for (auto ch : currentChannels) {
            if (release <= 0 || currentChannels.empty())
                break;
            currentChannels.erase(ch);
            release--;
        }
    }
}

void DFDMNode::vacateChannels() {
    for (auto ch : currentChannels) {
        ch->writeState(0);
    }
    currentChannels.clear();
}

int DFDMNode::numBroadcastingNodes() {
    std::set<int> seenIds;
    int count = 0;

    for (auto ch : channels) {
        int state = ch->readState();
        if (state > 0) {
            if (seenIds.count(state) == 0) {
                count++;
                seenIds.insert(state);
            }
        }
    }

    return count;
}