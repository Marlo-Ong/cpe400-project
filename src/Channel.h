#ifndef CHANNEL_H
#define CHANNEL_H

class Channel {
public:
    explicit Channel(int channelId);

    int id() const;
    int owner() const;
    bool isFree() const;

    void assign(int nodeId);
    void release();

private:
    int channelId;
    int ownerId;
};

#endif
