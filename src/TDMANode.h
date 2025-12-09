#ifndef TDMA_NODE
#define TDMA_NODE

#include "Node.h"

class TDMANode : public Node {
public:

    TDMANode(int nodeId)
    : Node(nodeId) {}

    void update() override;
};

#endif