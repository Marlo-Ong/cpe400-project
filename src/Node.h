#ifndef NODE_H
#define NODE_H

#include <random>
#include <memory>
#include "Channel.h"
#include <iostream>

class Node {
public:
    Node(int nodeId, std::shared_ptr<std::vector<Channel>> channels)
    : id(nodeId),
      channels(channels),
      remainingData(0),
      totalDataSent(0) {
        std::cout << "ch size: " << channels->size() << std::endl;
      }

    virtual void update(int time) = 0;

    int getId() const;
    int getRemainingData() const;
    int getAssignedChannels() const;
    bool broadcasting() const;
    int getTotalDataSent() const;

protected:
    const int id;
    std::shared_ptr<std::vector<Channel>> channels;
    int remainingData;
    int totalDataSent;
};

#endif
