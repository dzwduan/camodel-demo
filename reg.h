#pragma once

#include <cstdint>
#include "wire.h"

class Wire;

class Reg {

    public:
        Reg() : curr_val(0), next_val(0) {}
        Reg(uint32_t val) : curr_val(0), next_val(val) {}
        void write(uint32_t val) {
            next_val = val;
        }

        [[nodiscard]] constexpr uint32_t read() const{
            return curr_val;
        }

        void update() {
            curr_val = next_val;
        }

        // operator = 
        Reg& operator=(const Reg& reg) {
            next_val = reg.next_val;
            return *this;
        }

        Reg& operator=(const uint32_t val) {
            next_val = val;
            return *this;
        }

        // operator <<=
        Reg& operator<<=(const Reg& reg) {
            next_val = reg.curr_val;
            return *this;
        }

        Reg& operator<<=(const uint32_t val) {
            next_val = val;
            return *this;
        }

        friend Reg& operator<<=(Reg& reg, const Wire& wire);

    private:
        uint32_t curr_val;
        uint32_t next_val;
};


Reg& operator<<=(Reg& reg, const Wire& wire);
