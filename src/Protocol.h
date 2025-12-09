#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include <memory>

#include "Node.h"
#include "DFDMNode.h"
#include "TDMANode.h"

class Protocol {
    public: 

    enum Type {
        DFDM,
        TDMA,
    };

    static std::string name(Type type) {
        switch (type) {
            case Type::DFDM:
                return "Dynamic FDM";
            case Type::TDMA:
                return "TDMA";
            default:
                exit(1);
        }
    }
};

#endif
