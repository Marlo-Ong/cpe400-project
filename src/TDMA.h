#ifndef TDMA_H
#define TDMA_H

#include "Protocol.h"

class TDMA : public Protocol {
public:
    void update(std::vector<Node>& nodes, int time, int totalChannels) override;
    std::string name() const override;
};

#endif
