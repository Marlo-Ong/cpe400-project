#ifndef PACKET_H
#define PACKET_H

class Packet {
    int senderId;
public:
    Packet(int id) : senderId(id) {}
    Packet() = default;

    int id();
};

#endif