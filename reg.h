#pragma once

#include <cstdint>
#include <stdexcept>
#include <unordered_set>


class BasicReg {
    public:
    // C++17 允许通过 inline 关键字在类内直接定义静态成员变量
        inline static std::unordered_set<BasicReg *> reg_lists;

        virtual void update() = 0;
        virtual void reset() = 0;

        static void update_all() {
            for (auto &reg : reg_lists) {
                reg->update();
            }
        }
        
        static void reset_all() {
            for (auto &reg : reg_lists) {
                reg->reset();
            }
        }

        virtual ~BasicReg() = default;
};


template<typename T>
class Reg : public BasicReg{

    public:
        Reg() : curr_val(T()), next_val(T()), used(false) {
            reg_lists.insert(this);
        }
        Reg(T rst_val) : curr_val(rst_val), next_val(rst_val), used(false) {
            reg_lists.insert(this);
        }

        ~Reg() {
            reg_lists.erase(this);
        }

        void write(T val) {
            next_val = val;
            used = true;
        }

        constexpr T read() const {
            return curr_val;
        }

        void update() override{
            curr_val = next_val;
            used = false;
        }

        void reset() {
            curr_val = rst_val;
            next_val = rst_val;
            used = false;
        }

        // // operator = 
        // Reg& operator=(const Reg& reg) {
        //     if (used) {
        //         throw std::runtime_error("more than one write in one cycle");
        //     }
        //     next_val = reg.next_val;
        //     used = true;
        //     return *this;
        // }

        // Reg& operator=(const T val) {
        //     if (used) {
        //         throw std::runtime_error("more than one write in one cycle");
        //     }
        //     next_val = val;
        //     used = true;
        //     return *this;
        // }

        Reg& operator<<=(const Reg& reg) {
            next_val = reg.curr_val;
            used = true;
            return *this;
        }

        Reg& operator<<=(const T val) {
            next_val = val;
            used = true;
            return *this;
        }

    private:
        T curr_val;
        T next_val;
        T rst_val;
        bool used;
};
