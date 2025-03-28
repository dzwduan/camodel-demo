#pragma once
#include "fifo.h"
#include "reg.h"
#include <gtest/gtest.h>
#include <string>



// Fifo class tests
TEST(FifoTest, Empty) {
    Fifo<int, 4> fifo;    
    EXPECT_TRUE(fifo.isEmpty());
    EXPECT_FALSE(fifo.isFull());
    EXPECT_EQ(fifo.size(), 0);
}

TEST(FifoTest, WriteRead) {
    Fifo<int, 4> fifo;
    
    // Write a value
    EXPECT_TRUE(fifo.write(10));
    fifo.update();
    EXPECT_FALSE(fifo.isEmpty());
    EXPECT_EQ(fifo.size(), 1);
    
    // Read the value
    int val = 0;
    EXPECT_TRUE(fifo.read(val));
    EXPECT_EQ(val, 10);
    fifo.update();
    EXPECT_TRUE(fifo.isEmpty());
}

TEST(FifoTest, Full) {
    Fifo<int, 3> fifo;
    
    // Fill the FIFO
    EXPECT_TRUE(fifo.write(1));
    fifo.update();
    EXPECT_TRUE(fifo.write(2));
    fifo.update();
    EXPECT_TRUE(fifo.write(3));
    fifo.update();
    
    EXPECT_TRUE(fifo.isFull());
    EXPECT_EQ(fifo.size(), 3);
    
    // Should fail to write when full
    EXPECT_FALSE(fifo.write(4));
}

TEST(FifoTest, Peek) {
    Fifo<int, 3> fifo;
    
    EXPECT_TRUE(fifo.write(42));
    fifo.update();
    
    int val = 0;
    EXPECT_TRUE(fifo.peek(val));
    EXPECT_EQ(val, 42);
    
    // Peek shouldn't remove the value
    EXPECT_EQ(fifo.size(), 1);
    EXPECT_FALSE(fifo.isEmpty());
}

TEST(FifoTest, WrapAround) {
    Fifo<int, 3> fifo;
    
    // Fill the FIFO
    EXPECT_TRUE(fifo.write(1));
    fifo.update();
    EXPECT_TRUE(fifo.write(2));
    fifo.update();
    EXPECT_TRUE(fifo.write(3));
    fifo.update();
    
    // Read two values
    int val = 0;
    EXPECT_TRUE(fifo.read(val));
    fifo.update();
    EXPECT_EQ(val, 1);
    EXPECT_TRUE(fifo.read(val));
    EXPECT_EQ(val, 2);
    fifo.update();
    
    // Write two more values (should wrap around)
    EXPECT_TRUE(fifo.write(4));
    fifo.update();
    EXPECT_TRUE(fifo.write(5));
    fifo.update();
    
    // Read everything out in order
    EXPECT_TRUE(fifo.read(val));
    fifo.update();
    EXPECT_EQ(val, 3);
    EXPECT_TRUE(fifo.read(val));
    fifo.update();
    EXPECT_EQ(val, 4);
    EXPECT_TRUE(fifo.read(val));
    fifo.update();
    EXPECT_EQ(val, 5);
    fifo.update();
    
    EXPECT_TRUE(fifo.isEmpty());
}

TEST(FifoTest, Reset) {
    Fifo<int, 3> fifo;
    
    EXPECT_TRUE(fifo.write(1));
    fifo.update();
    EXPECT_TRUE(fifo.write(2));
    fifo.update();
    
    fifo.reset();
    fifo.update();
    EXPECT_TRUE(fifo.isEmpty());
    EXPECT_FALSE(fifo.isFull());
    EXPECT_EQ(fifo.size(), 0);
}

// Note: To run these tests, create a main.cpp file with:
/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/

