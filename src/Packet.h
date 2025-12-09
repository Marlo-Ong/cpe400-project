#ifndef PACKET_H
#define PACKET_H

// This packet data structure is just an abstraction of a packet
// containing some certain-sized payload, not a complete implementation
class Packet
{
public:
    Packet();
    explicit Packet(int size);

    int size() const;
    int remaining() const;
    int transmit(int amount);
    bool empty() const;

private:
    int totalSize;
    int remainingSize;
};

#endif
