#ifndef CHANNEL
#define CHANNEL

#include <utility>
#include "Packet.h"

class Channel {
public:
    enum State {
        Empty,
        Busy,
        Collided
    };

    Channel() : currentState(), nextState() {}

    Packet readPacket();
    void sendPacket(Packet packet);
    void advanceState();

    bool isEmpty();
    bool isBusy();
    bool isCollided();

private:
    std::pair<State, Packet> currentState;
    std::pair<State, Packet> nextState;
  
};



#endif