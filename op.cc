#include "wire.h"
#include "reg.h"




Wire& Wire::operator=(const Reg& reg) {
    this->write(reg.read());
    return *this;
}

Reg& Reg::operator<<=(const Wire& wire) {
    this->write(wire.read());
    return *this;
}

// std::unordered_set<BasicReg*> BasicReg::reg_lists; 