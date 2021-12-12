#include <gtest/gtest.h>

#include "vm/vm.hpp"
#include "instruction_builder.hpp"

#include <algorithm>

using namespace lc3::vm;
using namespace lc3::test;

TEST(vm, memory_size_should_be_ffff) {
    const memory_t memory{};
    ASSERT_EQ(0xffff, memory.size());
}

TEST(vm, load_bytecode) {
    memory_t memory{};
    std::vector<uint16_t> bytecode {1,2,3,4,5};
    load(memory, bytecode, 0x1000);

    ASSERT_TRUE(std::equal(std::begin(bytecode), std::end(bytecode), &memory[0x1000]));
}

TEST(add_instr, add_two_registers) {
    memory_t memory{};
    registers_t registers{};

    auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    registers[R1] = 10;
    registers[R2] = 20;

    execute(memory, registers, instr);

    ASSERT_EQ(30, registers[R0]);
}

TEST(add_instr, add_condition_flags_positive) {
    memory_t memory{};
    registers_t registers{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    registers[R1] = 10;
    registers[R2] = 20;

    execute(memory, registers, instr);

    ASSERT_EQ(flags_t::Positive, registers[CND]);
}

TEST(add_instr, add_condition_flags_negative) {
    memory_t memory{};
    registers_t registers{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    registers[R1] = 10;
    registers[R2] = -20;

    execute(memory, registers, instr);

    ASSERT_EQ(flags_t::Negative, registers[CND]);
}

TEST(add_instr, add_condition_flags_zero) {
    memory_t memory{};
    registers_t registers{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    registers[R1] = 10;
    registers[R2] = -10;

    execute(memory, registers, instr);

    ASSERT_EQ(flags_t::Zero, registers[CND]);
}

TEST(add_instr, add_with_immediate) {
    memory_t memory{};
    registers_t registers{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .immediate(0x8)
        .build();

    registers[R1] = 8;

    execute(memory, registers, instr);

    ASSERT_EQ(16, registers[R0]);
}

TEST(and_instr, and_two_registers) {
    memory_t memory{};
    registers_t registers{};

    const auto instr = instruction_builder_t{}
        .binary_and()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    registers[R1] = 0xf0f0;
    registers[R2] = 0x00f0;

    execute(memory, registers, instr);

    ASSERT_EQ(0x00f0, registers[R0]);
}

TEST(and_instr, and_immediate) {
    memory_t memory{};
    registers_t registers{};

    const auto instr = instruction_builder_t{}
        .binary_and()
        .destination_register(R0)
        .source_register_1(R1)
        .immediate(0xE)
        .build();

    registers[R1] = 0xf0fa;

    execute(memory, registers, instr);

    ASSERT_EQ(0xa, registers[R0]);
}
