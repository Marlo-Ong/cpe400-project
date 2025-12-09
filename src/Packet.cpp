#include "Packet.h"

#include <algorithm>

Packet::Packet() : totalSize(0), remainingSize(0) {}

Packet::Packet(int size) : totalSize(size), remainingSize(size) {}
int Packet::size() const
{
    return totalSize;
}

int Packet::remaining() const
{
    return remainingSize;
}

int Packet::transmit(int amount)
{
    // Trim the amount from the remainder and subtract it from the payload
    if (remainingSize <= 0 || amount <= 0)
    {
        return 0;
    }
    int sent = std::min(remainingSize, amount);
    remainingSize -= sent;
    return sent;
}

bool Packet::empty() const
{
    return remainingSize <= 0;
}
