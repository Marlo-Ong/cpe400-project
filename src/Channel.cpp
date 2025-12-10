#include "Channel.h"

Packet Channel::readPacket() {
    return currentState.second;
}

void Channel::sendPacket(Packet packet) {
    if (nextState.first == State::Empty) {
        nextState.second = packet;
    } else {
        nextState.first = State::Collided;
        nextState.second = Packet();
    }
}

void Channel::advanceState() {
    currentState = nextState;
    nextState = {State::Empty, Packet()};
}

bool Channel::isEmpty() { return currentState.first == State::Empty; }
bool Channel::isBusy() { return currentState.first == State::Busy; }
bool Channel::isCollided() { return currentState.first == State::Collided; }