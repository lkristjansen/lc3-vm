#include <gtest/gtest.h>

#include "vm/opcode.hpp"

using namespace lc3::vm;

TEST(opcode, opcode_type) {
    ASSERT_EQ(0xf, opcode(0xf000));
}

TEST(sign_extend, negative_zero) {
    const uint16_t instr{0x8}; 
    ASSERT_EQ(0xfff8, sign_extend(instr, 3));
}

TEST(sign_extend, zero) {
    const uint16_t instr{0x0};
    ASSERT_EQ(0x0, sign_extend(instr, 3));
}

TEST(sign_extend, negative_number) {
    const uint16_t instr{0xe};
    ASSERT_EQ(0xfffe, sign_extend(instr, 3));
}

TEST(sign_extend, positive_number) {
    const uint16_t instr{0x6};
    ASSERT_EQ(0x6, sign_extend(instr, 3));
}

TEST(use_immediate, should_use_intermediate) {
    ASSERT_TRUE(use_immediate(0xffff));
    ASSERT_TRUE(use_immediate(0x0020));
}

TEST(use_immediate, should_not_use_intermediate) {
    ASSERT_FALSE(use_immediate(0x0000));
    ASSERT_FALSE(use_immediate(0xffdf));
}

TEST(immediate, negative_value) {
    ASSERT_EQ(0xffff, immediate(0x001f));
}

TEST(immediate, max_value) {
    ASSERT_EQ(0xf, immediate(0x000f));
}

TEST(immediate, zero_value) {
    ASSERT_EQ(0, immediate(0xffe0));
}

TEST(destination_register, max_value) {
    ASSERT_EQ(7, destination_register(0x0e00));
}

TEST(destination_register, zero_value) {
    ASSERT_EQ(0, destination_register(0xf1ff));
}

TEST(source_register_1, max_value) {
    ASSERT_EQ(7, source_register_1(0x01c0));
}

TEST(source_register_1, zero_value) {
    ASSERT_EQ(0, source_register_1(0xfe3f));
}

TEST(source_register_2, max_value) {
    ASSERT_EQ(7, source_register_2(0x0007));
}

TEST(source_register_2, zero_value) {
    ASSERT_EQ(0, source_register_2(0xfff8));
}
