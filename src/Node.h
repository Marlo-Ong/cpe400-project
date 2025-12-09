#ifndef NODE_H
#define NODE_H

#include <random>

class Node {
public:
    Node(int nodeId)
    : id(nodeId),
      remainingData(0),
      assignedChannels(0),
      nextDataArrivalTime(0),
      isBroadcasting(false),
      totalDataSent(0) {}

    virtual void update() = 0;
    int transmit(int requestedChannels);

    int getId() const;
    int getRemainingData() const;
    int getAssignedChannels() const;
    bool broadcasting() const;
    int getTotalDataSent() const;

protected:
    int id;
    int remainingData;
    int assignedChannels;
    int nextDataArrivalTime;
    bool isBroadcasting;
    int totalDataSent;
    static constexpr int kMinPacketSize = 5;
    static constexpr int kMaxPacketSize = 20;
    static constexpr int kMinIdleGap = 3;
    static constexpr int kMaxIdleGap = 8;

    void scheduleNextArrival(int currentTime);
    static int randomInRange(int min, int max);

    static std::mt19937& generator();
};

#endif
