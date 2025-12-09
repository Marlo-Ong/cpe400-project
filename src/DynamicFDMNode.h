#ifndef DYNAMIC_FDM_NODE
#define DYNAMIC_FDM_NODE

#include "Node.h"

class DynamicFDMNode : public Node {
    // The zeroth channel is used for coordination between nodes
    static constexpr int coordinationChannel = 0;
public: 

    DynamicFDMNode(int nodeId, std::vector<Channel>& channels)
    : Node(nodeId, channels) {}

    void update(int time) override;
};


#endif