#ifndef DYNAMIC_FDM_NODE
#define DYNAMIC_FDM_NODE

#include "Node.h"

#include <set>

class DFDMNode : public Node {
    // The zeroth channel is used for coordination between nodes
    std::shared_ptr<Channel> coordChannel;

    std::set<std::shared_ptr<Channel>> currentChannels;

public: 

    DFDMNode(int nodeId, std::vector<std::shared_ptr<Channel>> channels)
    : Node(nodeId, channels), currentChannels() {}

    void update(int time) override;

private:

    void allowNewcomer(int id);
    void vacateChannels();
    std::set<int> broadcastingNodes();
};


#endif