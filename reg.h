#pragma once

#include <cstdint>
#include <unordered_set>
#include "wire.h"

class Wire;

class BasicReg {
    public:
    // C++17 允许通过 inline 关键字在类内直接定义静态成员变量
        inline static std::unordered_set<BasicReg *> reg_lists;
        virtual void update() = 0;

        static void update_all() {
            for (auto &reg : reg_lists) {
                reg->update();
            }
        }

        virtual ~BasicReg() = default;
};

class Reg : public BasicReg{

    public:
        Reg() : curr_val(0), next_val(0) {
            reg_lists.insert(this);
        }
        Reg(uint32_t val) : curr_val(0), next_val(val) {
            reg_lists.insert(this);
        }

        void write(uint32_t val) {
            next_val = val;
        }

        constexpr uint32_t read() const {
            return curr_val;
        }

        void update() override{
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

        Reg& operator<<=(const Wire& wire);

    private:
        uint32_t curr_val;
        uint32_t next_val;
};



