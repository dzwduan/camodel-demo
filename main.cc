#include "gtest/gtest.h"
#include "wire.h"
#include "reg.h"

TEST(WireTest, WriteRead) {
    Wire wire;
    wire.write(0x12345678);
    EXPECT_EQ(wire.read(), 0x12345678);
}

TEST(RegTest, WriteRead) {
    Reg reg;
    reg.write(0x12345678);
    EXPECT_EQ(reg.read(), 0);
    reg.update();
    EXPECT_EQ(reg.read(), 0x12345678);
}

TEST(RegWireTest, WriteRead) {
    Wire wire;
    Reg reg;
    wire.write(0x12345678);
    reg <<= wire;
    EXPECT_EQ(reg.read(), 0);
    reg.update();
    EXPECT_EQ(reg.read(), 0x12345678);
    wire << reg;
    EXPECT_EQ(wire.read(), 0x12345678);
}

TEST(RegWireTest, WriteRead2) {
    Wire wire;
    Reg reg1;
    Reg reg2;
    wire.write(0x12345678);
    reg1 <<= wire;
    reg2 <<= reg1;
    EXPECT_EQ(reg1.read(), 0);
    EXPECT_EQ(reg2.read(), 0);
    reg1.update();
    reg2.update();
    EXPECT_EQ(reg1.read(), 0x12345678);
    EXPECT_EQ(reg2.read(), 0);
    wire << reg1;
    EXPECT_EQ(wire.read(), 0x12345678);
    reg2 <<= wire;
    reg2.update();
    EXPECT_EQ(reg2.read(), 0x12345678);
}

// wire << wire
TEST(WireTest, WireToWire) {
    Wire wire1;
    Wire wire2;
    wire1.write(0x12345678);
    wire2 << wire1;
    EXPECT_EQ(wire2.read(), 0x12345678);
}

// wire << reg
TEST(WireTest, RegToWire) {
    Wire wire;
    Reg reg;
    reg.write(0x87654321);
    reg.update();
    EXPECT_EQ(reg.read(), 0x87654321);
    wire << reg;
    EXPECT_EQ(wire.read(), 0x87654321);
}

// wire << reg <<= wire
TEST(WireRegTest, WireRegWire) {
    Wire wire1;
    Wire wire2;
    Reg reg;
    wire1.write(0xABCDEF01);
    reg <<= wire1;
    reg.update();
    EXPECT_EQ(reg.read(), 0xABCDEF01);
    wire2 << reg;
    EXPECT_EQ(wire2.read(), 0xABCDEF01);
}

// reg <<= wire << reg
TEST(RegWireTest, RegWireReg) {
    Wire wire;
    Reg reg1;
    Reg reg2;
    reg1.write(0x11223344);
    reg1.update();
    wire << reg1;
    EXPECT_EQ(wire.read(), 0x11223344);
    reg2 <<= wire;
    reg2.update();
    EXPECT_EQ(reg2.read(), 0x11223344);
}

// reg <<= wire << reg <<= wire
TEST(RegWireTest, ComplexChain) {
    Wire wire1;
    Wire wire2;
    Reg reg1;
    Reg reg2;
    
    wire1.write(0xDEADBEEF);
    reg1 <<= wire1;
    reg1.update();
    EXPECT_EQ(reg1.read(), 0xDEADBEEF);
    
    wire2 << reg1;
    EXPECT_EQ(wire2.read(), 0xDEADBEEF);
    
    reg2 <<= wire2;

    EXPECT_EQ(reg2.read(), 0);

    wire1.write(0xCAFEBABE);
    reg1 <<= wire1;
    reg1.update();
    EXPECT_EQ(reg1.read(), 0xCAFEBABE);

    wire2 << reg1;
    EXPECT_EQ(wire2.read(), 0xCAFEBABE);
    reg2 <<= wire2;
    reg2.update();
    EXPECT_EQ(reg2.read(), 0xCAFEBABE);
}

// unit test main
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}