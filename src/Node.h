#ifndef NODE_H
#define NODE_H

#include <random>
#include <memory>
#include "Channel.h"
#include <iostream>

class Node {
public:
    Node(int nodeId, std::vector<std::shared_ptr<Channel>> channels)
    : id(nodeId),
      channels(channels),
      dataToSend(0),
      totalDataSent(0) {}

    virtual void update(int time) = 0;

    int getId() const;
    int getdataToSend() const;
    int getAssignedChannels() const;
    bool broadcasting() const;
    int getTotalDataSent() const;
    void injectData(int amount);

protected:
    const int id;
    std::vector<std::shared_ptr<Channel>> channels;
    int dataToSend;
    int totalDataSent;
};

#endif
