#ifndef DYNAMIC_FDM_NODE
#define DYNAMIC_FDM_NODE

#include "Node.h"

class DynamicFDMNode : public Node {
public: 

    DynamicFDMNode(int nodeId, std::vector<Channel>& channels)
    : Node(nodeId, channels) {}

    void update(int time) override;
};


#endif