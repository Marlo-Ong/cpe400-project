#ifndef CHANNEL
#define CHANNEL

class Channel {
    // If the state is 0, the channel is unused
    // If the state is -1, a collision occured
    // Otherwise, the number in state is the id of the node who last sent a packet 
    int currentState;
    int nextState;

public:
    Channel() : currentState(0), nextState(0) {}

    int readState();
    void writeState(int packet);
    void advanceState();
};

#endif