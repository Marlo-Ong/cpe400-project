#include "Channel.h"

int Channel::readState() {
    return currentState;
}

void Channel::writeState(int packet) {
    if (nextState == 0) {
        nextState = packet;
    } else {
        nextState = -1;
    }
}

void Channel::advanceState() {
    currentState = nextState;
    nextState = 0;
}