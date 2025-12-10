#include "DFDMNode.h"

void DFDMNode::update(int time) {
    if (dataToSend <= 0) {
        vacateChannels();
        return;
    }
    
    //check for available channels
    for (auto ch : channels) {
        if (ch->isEmpty()) {
            currentChannels.insert(ch);
        
        } else if (ch->isCollided()) {
            // if one of the channels we held had a collision, stop using it for now
            currentChannels.erase(ch);
        }
    }
    
    if (!currentChannels.empty()) {
        // send data through the currently held channels
        for (auto ch : currentChannels) {
            ch->sendPacket(id);
            dataToSend--;
            totalDataSent++;
            if (dataToSend <= 0) {
                vacateChannels();
                break;
            }
        }
    } else {
        // request channels on commumication channel
        coordChannel->sendPacket(id);
    }

    // if another node is requesting channels, free up some of ours
    if (!coordChannel->isEmpty()) {

        std::set<int> broadcasting = broadcastingNodes();
        int numB = broadcasting.size();

        // each node should relinquish C / n(n+1) channels
        int release = (channels.size() - 1) / (numB * (numB + 1));
        for (auto ch : currentChannels) {
            if (release <= 0 || currentChannels.empty())
                break;
            currentChannels.erase(ch);
            release--;
        }
    }
}

void DFDMNode::allowNewcomer(int id) {
    
}

void DFDMNode::vacateChannels() {
    for (auto ch : currentChannels) {
        ch->sendPacket(0);
    }
    currentChannels.clear();
}

std::set<int> DFDMNode::broadcastingNodes() {
    std::set<int> nodes;

    for (auto channel : channels) {
        int state = channel->readPacket().id();
        if (state > 0) {
            if (nodes.count(state) == 0) {
                nodes.insert(state);
            }
        }
    }

    return nodes;
}