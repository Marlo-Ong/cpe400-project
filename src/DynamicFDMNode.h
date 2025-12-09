#ifndef DYNAMIC_FDM_NODE
#define DYNAMIC_FDM_NODE

#include "Node.h"

class DynamicFDMNode : public Node {
public: 

    DynamicFDMNode(int nodeId)
    : Node(nodeId) {}

    void update() override;
};


#endif