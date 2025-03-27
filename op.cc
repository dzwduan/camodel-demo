#include "wire.h"
#include "reg.h"


Wire& operator<<(Wire& wire, Reg& reg) {
    wire.write(reg.read());
    return wire;
}

Reg& operator<<=(Reg& reg, const Wire& wire) {
    reg.write(wire.read());
    return reg;
}