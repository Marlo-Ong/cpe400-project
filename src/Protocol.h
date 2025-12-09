#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include <memory>

#include "Node.h"
#include "DFDMNode.h"
#include "FDMANode.h"
#include "TDMANode.h"

class Protocol {
    public: 

    enum Type {
        DFDM,
        TDMA,
        FDMA,
    };

    static std::string name(Type type) {
        switch (type) {
            case Type::DFDM:
                return "Dynamic FDM";
            case Type::TDMA:
                return "TDMA";
            case Type::FDMA:
                return "FDMA";
            default:
                exit(1);
        }
    }
};

#endif
