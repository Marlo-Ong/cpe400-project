#include "Node.h"

#include <algorithm>

int Node::transmit(int requestedChannels) {
    if (!isBroadcasting || requestedChannels <= 0) {
        assignedChannels = 0;
        return 0;
    }

    assignedChannels = requestedChannels;
    int sent = std::min(remainingData, requestedChannels);
    remainingData -= sent;
    totalDataSent += sent;

    if (remainingData == 0) {
        isBroadcasting = false;
        assignedChannels = 0;
    }

    return sent;
}

int Node::getId() const { return id; }

int Node::getRemainingData() const { return remainingData; }

int Node::getAssignedChannels() const { return assignedChannels; }

bool Node::broadcasting() const { return isBroadcasting; }

int Node::getTotalDataSent() const { return totalDataSent; }

void Node::scheduleNextArrival(int currentTime) {
    nextDataArrivalTime = currentTime + randomInRange(kMinIdleGap, kMaxIdleGap);
}

int Node::randomInRange(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator());
}

std::mt19937& Node::generator() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}
