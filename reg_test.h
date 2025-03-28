#pragma once
#include "gtest/gtest.h"
#include "reg.h"
TEST(RegTest, DefaultConstructor) {
    Reg<int> reg;
    EXPECT_EQ(reg.read(), 0);
}

TEST(RegTest, ValueConstructor) {
    Reg<int> reg(42);
    EXPECT_EQ(reg.read(), 42); // curr_val is 0 until update
    reg <<= 33;
    reg.update();
    EXPECT_EQ(reg.read(), 33);
}

TEST(RegTest, WriteAndRead) {
    Reg<int> reg;
    reg.write(42);
    EXPECT_EQ(reg.read(), 0);
    reg.update();
    EXPECT_EQ(reg.read(), 42);
}

TEST(RegTest, AssignmentOperator) {
    Reg<int> reg1;
    Reg<int> reg2(42);
    reg1 <<= reg2;
    EXPECT_EQ(reg1.read(), 0);
    reg1.update();
    EXPECT_EQ(reg1.read(), 42);
}

TEST(RegTest, ValueAssignmentOperator) {
    Reg<int> reg;
    reg = 42;
    EXPECT_EQ(reg.read(), 42);
}

TEST(RegTest, LeftShiftAssignmentOperator) {
    Reg<int> reg1;
    Reg<int> reg2(42);
    reg2.update();
    reg1 <<= reg2;
    EXPECT_EQ(reg1.read(), 0);
    reg1.update();
    EXPECT_EQ(reg1.read(), 42);
}

TEST(RegTest, LeftShiftAssignmentWithValue) {
    Reg<int> reg;
    reg <<= 42;
    EXPECT_EQ(reg.read(), 0);
    reg.update();
    EXPECT_EQ(reg.read(), 42);
}

TEST(RegTest, UpdateAll) {
    Reg<int> reg1(1);
    Reg<int> reg2(2);
    BasicReg::update_all();
    EXPECT_EQ(reg1.read(), 1);
    EXPECT_EQ(reg2.read(), 2);
}

TEST(RegTest, DifferentTypes) {
    Reg<int> intReg;
    Reg<double> doubleReg(3.14);
    
    intReg <<= 1;
    // if intReg <<= 2; runtime error
    
    BasicReg::update_all();
    
    EXPECT_EQ(intReg.read(), 1);
    EXPECT_DOUBLE_EQ(doubleReg.read(), 3.14);
}
