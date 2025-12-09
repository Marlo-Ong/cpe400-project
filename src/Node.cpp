#include "Node.h"

#include <algorithm>

// int Node::transmit(int requestedChannels) {
//     if (!isBroadcasting || requestedChannels <= 0) {
//         assignedChannels = 0;
//         return 0;
//     }

//     assignedChannels = requestedChannels;
//     int sent = std::min(remainingData, requestedChannels);
//     remainingData -= sent;
//     totalDataSent += sent;

//     if (remainingData == 0) {
//         isBroadcasting = false;
//         assignedChannels = 0;
//     }

//     return sent;
// }

int Node::getId() const { return id; }

int Node::getRemainingData() const { return remainingData; }

int Node::getTotalDataSent() const { return totalDataSent; }