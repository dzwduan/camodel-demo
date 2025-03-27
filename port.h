#pragma once

#include <string>
#include <cstdint>
#include <sys/types.h>
#include "module.h"
#include "reg.h"
#include <unordered_set>


class Port {
    public:
        inline static std::unordered_set<Port *> port_lists;

        Port(std::string name, Module* module) : name(name), module(module) {
            port_lists.insert(this);
        }
        virtual ~Port() {
            port_lists.erase(this);
        }

        std::string getName() const {
            return name;
        }

        Module* getModule() const {
            return module;
        }


        virtual void update() = 0;

    protected:
        std::string name;
        Module* module;
};



template <typename T>
class InPort : public Port {
    public:
        InPort(std::string name, Module* module) : Port(name, module) {}
        virtual ~InPort() = default;


        void update() override {

        }

    private:
        std::string name;
        Module* module;

};

template<typename T>
class OutPort : public Port {
    public:
        OutPort(std::string name, Module* module) : Port(name, module) {}
        virtual ~OutPort() = default;

        void connect() {

        }

        void update() override {

        }

    private:
        std::string name;
        Module* module;
        Reg<T> val;
};