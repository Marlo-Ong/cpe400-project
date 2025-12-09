#include "Node.h"

#include <algorithm>

Node::Node(int nodeId)
    : id(nodeId),
      remainingData(0),
      assignedChannels(0),
      nextDataArrivalTime(0),
      isBroadcasting(false),
      totalDataSent(0),
      currentPacket() {}

void Node::update(int time)
{
    // When idle and the next arrival time is reached, create packet
    if (!isBroadcasting && time >= nextDataArrivalTime)
    {
        int packetSize = randomInRange(kMinPacketSize, kMaxPacketSize);
        currentPacket = Packet(packetSize);
        remainingData = currentPacket.remaining();
        isBroadcasting = true;
        scheduleNextArrival(time);
    }
}

int Node::transmit()
{
    int requestedChannels = static_cast<int>(ownedChannels.size());
    // Ignore transmissions when idle or when no channels are owned.
    if (!isBroadcasting || requestedChannels <= 0)
    {
        assignedChannels = 0;
        return 0;
    }

    assignedChannels = requestedChannels;

    // Consume as much of the packet as the allocated bandwidth allows.
    int sent = currentPacket.transmit(requestedChannels);
    remainingData = currentPacket.remaining();
    totalDataSent += sent;

    if (currentPacket.empty())
    {
        isBroadcasting = false;
        assignedChannels = 0;
        remainingData = 0;
    }

    return sent;
}

int Node::getId() const { return id; }

int Node::getRemainingData() const { return remainingData; }

int Node::getAssignedChannels() const { return assignedChannels; }

bool Node::broadcasting() const { return isBroadcasting; }

int Node::getTotalDataSent() const { return totalDataSent; }

void Node::clearChannels()
{
    ownedChannels.clear();
    assignedChannels = 0;
}

void Node::addChannel(int channelId)
{
    ownedChannels.push_back(channelId);
    assignedChannels = static_cast<int>(ownedChannels.size());
}

void Node::scheduleNextArrival(int currentTime)
{
    nextDataArrivalTime = currentTime + randomInRange(kMinIdleGap, kMaxIdleGap);
}

int Node::randomInRange(int min, int max)
{
    // basic helper for uniformly distributed arrival/size parameters
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator());
}

std::mt19937 &Node::generator()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}
