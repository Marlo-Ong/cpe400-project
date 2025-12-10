#ifndef TDMA_NODE
#define TDMA_NODE

#include "Node.h"

class TDMANode : public Node {
    const int numNodes;
    const int assignedTime;

public:

    TDMANode(int nodeId, std::vector<std::shared_ptr<Channel>> channels, int numNodes, int assignedTime)
    : Node(nodeId, channels), 
      numNodes(numNodes), 
      assignedTime(assignedTime) {}

    void update(int time) override;

private:
    
    bool isAssigned(int time);
};

#endif