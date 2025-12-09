#ifndef DYNAMIC_FDM_H
#define DYNAMIC_FDM_H

#include "Protocol.h"

class DynamicFDM : public Protocol {
public:
    void update(std::vector<Node>& nodes, std::vector<Channel>& channels, int time) override;
    std::string name() const override;
};

#endif
