#pragma once

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include "reg.h"


// FIFO implementation using registers
template <typename T, size_t DEPTH>
class Fifo {
private:
    std::vector<Reg<T>> data;
    Reg<uint32_t> write_ptr;
    Reg<uint32_t> read_ptr;
    Reg<uint32_t> count;
    Reg<bool> empty;
    Reg<bool> full;

public:
    Fifo() {
        empty.write(true);
        empty.update();
        for (size_t i = 0; i < DEPTH; i++) {
            data.push_back(Reg<T>());
        }
    }

    bool isEmpty() const {
        return empty.read();
    }

    bool isFull() const {
        return full.read();
    }

    uint32_t size() const {
        return count.read();
    }

    bool write(const T& value) {
        if (full.read()) {
            return false;
        }

        data[write_ptr.read()].write(value);
        uint32_t next_write_ptr = (write_ptr.read() + 1) % DEPTH;
        write_ptr.write(next_write_ptr);

        int next_count = count.read() + 1;
        count <<= next_count;

        full.write(next_count == DEPTH);
        empty.write(false);

        return true;
    }

    bool read(T& value) {
        if (empty.read()) {
            return false;
        }

        value = data[read_ptr.read()].read();
        uint32_t next_read_ptr = (read_ptr.read() + 1) % DEPTH;
        read_ptr.write(next_read_ptr);

        uint32_t next_count = count.read() - 1;
        count.write(next_count);

        full.write(false);
        empty.write(next_count == 0);

        return true;
    }

    bool peek(T& value) const {
        if (empty.read()) {
            return false;
        }
        
        value = data[read_ptr.read()].read();
        return true;
    }

    void update() {
        // First update internal registers
        for (auto& reg : data) {
            reg.update();
        }
        
        // Then update control registers
        write_ptr.update();
        read_ptr.update();
        count.update();
        empty.update();
        full.update();
    }

    void reset() {
        write_ptr.write(0);
        read_ptr.write(0);
        count.write(0);
        empty.write(true);
        full.write(false);
    }
};


