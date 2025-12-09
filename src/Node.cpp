#include "Node.h"

#include <algorithm>

// int Node::transmit(int requestedChannels) {
//     if (!isBroadcasting || requestedChannels <= 0) {
//         assignedChannels = 0;
//         return 0;
//     }

//     assignedChannels = requestedChannels;
//     int sent = std::min(dataToSend, requestedChannels);
//     dataToSend -= sent;
//     totalDataSent += sent;

//     if (dataToSend == 0) {
//         isBroadcasting = false;
//         assignedChannels = 0;
//     }

//     return sent;
// }

int Node::getId() const { return id; }

int Node::getdataToSend() const { return dataToSend; }

int Node::getTotalDataSent() const { return totalDataSent; }