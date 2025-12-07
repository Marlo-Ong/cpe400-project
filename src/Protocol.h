#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>

#include "Node.h"

class Protocol {
public:
    virtual ~Protocol() {}
    virtual void update(std::vector<Node>& nodes, int time, int totalChannels) = 0;
    virtual std::string name() const = 0;
};

#endif
