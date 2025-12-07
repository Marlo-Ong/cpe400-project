#ifndef NODE_H
#define NODE_H

#include <random>

class Node {
public:
    explicit Node(int nodeId);

    void update(int time);
    int transmit(int requestedChannels);

    int getId() const;
    int getRemainingData() const;
    int getAssignedChannels() const;
    bool broadcasting() const;
    int getTotalDataSent() const;

private:
    int id;
    int remainingData;
    int assignedChannels;
    int nextDataArrivalTime;
    bool isBroadcasting;
    int totalDataSent;

    void scheduleNextArrival(int currentTime);
    static int randomInRange(int min, int max);

    static std::mt19937& generator();
};

#endif
