#include "gtest/gtest.h"
#include "reg.h"
#include <cstdint>


class TestReg : public ::testing::Test {
protected:
    void SetUp() override {
        reg = new Reg<int>(0);
    }

    void TearDown() override {
        delete reg;
    }

    Reg<int> *reg;
};

TEST_F(TestReg, test1) {
    EXPECT_EQ(*reg, 0);
    *reg <<= 1;
    EXPECT_EQ(*reg, 0);
    reg->update();
    EXPECT_EQ(*reg, 1);
}

TEST_F(TestReg, test2) {
    EXPECT_EQ(*reg, 0);
    *reg <<= 1;
    EXPECT_EQ(*reg, 0);
    reg->update();
    EXPECT_EQ(*reg, 1);
    *reg <<= 2;
    EXPECT_EQ(*reg, 1);
    reg->update();
    EXPECT_EQ(*reg, 2);
}

TEST_F(TestReg, test_w_cnt) {
    EXPECT_EQ(*reg, 0);
    *reg <<= 1;
    *reg <<= 2;
}


// write a fifo test using reg
class Fifo {

};


    


// unit test main
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


