#ifndef NODE_H
#define NODE_H

#include <random>
#include <vector>

#include "Packet.h"

class Node
{
public:
  explicit Node(int nodeId);

  void update(int time);
  int transmit();
  void clearChannels();
  void addChannel(int channelId);

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
  Packet currentPacket;
  std::vector<int> ownedChannels;
  static constexpr int kMinPacketSize = 5;
  static constexpr int kMaxPacketSize = 20;
  static constexpr int kMinIdleGap = 3;
  static constexpr int kMaxIdleGap = 8;

  void scheduleNextArrival(int currentTime);
  static int randomInRange(int min, int max);

  static std::mt19937 &generator();
};

#endif
