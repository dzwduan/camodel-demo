#pragma once

#include <cstdint>

class Reg;

class Wire {
    public:
        Wire() : val(0) {}
        Wire(uint32_t val) : val(val) {}

        constexpr void write(uint32_t val) {
            this->val = val;
        }

        [[nodiscard]] constexpr uint32_t read() const{
            return val;
        }

        // operator =
        Wire& operator=(const Wire& wire) {
            val = wire.val;
            return *this;
        }

        Wire& operator=(const uint32_t val) {
            this->val = val;
            return *this;
        }

        // operator <<=
        Wire& operator<<(const Wire& wire) {
            val = wire.val;
            return *this;
        }

        Wire& operator<<(const uint32_t val) {
            this->val = val;
            return *this;
        }

        Wire& operator=(const Reg& reg);

        uint32_t val;
};
