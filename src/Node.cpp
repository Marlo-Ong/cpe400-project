#include "Node.h"

#include <algorithm>

int Node::getId() const { return id; }

int Node::getdataToSend() const { return dataToSend; }

int Node::getTotalDataSent() const { return totalDataSent; }

void Node::injectData(int amount) {
    if (amount <= 0) {
        return;
    }
    dataToSend += amount;
}
