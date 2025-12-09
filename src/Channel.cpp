#include "Channel.h"

Channel::Channel(int channelId)
    : channelId(channelId), ownerId(-1) {}

int Channel::id() const {
    return channelId;
}

int Channel::owner() const {
    return ownerId;
}

bool Channel::isFree() const {
    return ownerId < 0;
}

void Channel::assign(int nodeId) {
    ownerId = nodeId;
}

void Channel::release() {
    ownerId = -1;
}
