#ifndef FDMA_NODE
#define FDMA_NODE

#include "Node.h"

#include <vector>

class FDMANode : public Node {
public:
    FDMANode(int nodeId, std::vector<Channel>& channels, int totalNodes);

    void update(int time) override;

private:
    std::vector<int> ownedChannels;
};

#endif
