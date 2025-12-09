#ifndef TDMA_H
#define TDMA_H

#include "Protocol.h"

class TDMA : public Protocol {
public:
    void update(std::vector<Node>& nodes, std::vector<Channel>& channels, int time) override;
    std::string name() const override;
};

#endif
