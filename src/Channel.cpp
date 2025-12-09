#include "Channel.h"

bool Channel::isLocked() {
    return locked;
}

void Channel::lock() {
    locked = true;
}

void Channel::unlock() {
    locked = false;
}