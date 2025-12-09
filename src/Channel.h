#ifndef CHANNEL
#define CHANNEL

class Channel {
    bool locked;

public:
    Channel() : locked(false) {}

    bool isLocked();
    void lock();
    void unlock();
};

#endif