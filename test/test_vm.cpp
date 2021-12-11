#include <gtest/gtest.h>

#include "vm/vm.hpp"
#include "instruction_builder.hpp"

#include <algorithm>

using namespace lc3::vm;
using namespace lc3::test;

TEST(vm, memory_is_zeroed) {
    const vm_t vm{};
    constexpr auto is_zero = [] (const auto word) { return word == 0; };
    const bool all_zero = std::all_of(std::begin(vm.memory), std::end(vm.memory), is_zero);
    ASSERT_TRUE(all_zero);
}

TEST(vm, memory_size_should_be_ffff) {
    const vm_t vm{};
    ASSERT_EQ(0xffff, vm.memory.size());
}

TEST(vm, load_bytecode) {
    vm_t vm{};
    std::vector<uint16_t> bytecode {1,2,3,4,5};
    vm.load(bytecode, 0x1000);

    ASSERT_TRUE(std::equal(std::begin(bytecode), std::end(bytecode), &vm.memory[0x1000]));
}

TEST(add_instr, add_two_registers) {
    vm_t vm{};

    auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    vm.registers[R1] = 10;
    vm.registers[R2] = 20;

    vm.execute(instr);

    ASSERT_EQ(30, vm.registers[R0]);
}

TEST(add_instr, add_condition_flags_positive) {
    vm_t vm{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    vm.registers[R1] = 10;
    vm.registers[R2] = 20;

    vm.execute(instr);

    ASSERT_EQ(flags_t::Positive, vm.registers[CND]);
}

TEST(add_instr, add_condition_flags_negative) {
    vm_t vm{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    vm.registers[R1] = 10;
    vm.registers[R2] = -20;

    vm.execute(instr);

    ASSERT_EQ(flags_t::Negative, vm.registers[CND]);
}

TEST(add_instr, add_condition_flags_zero) {
    vm_t vm{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    vm.registers[R1] = 10;
    vm.registers[R2] = -10;

    vm.execute(instr);

    ASSERT_EQ(flags_t::Zero, vm.registers[CND]);
}

TEST(add_instr, add_with_immediate) {
    vm_t vm{};

    const auto instr = instruction_builder_t{}
        .add()
        .destination_register(R0)
        .source_register_1(R1)
        .immediate(0x8)
        .build();

    vm.registers[R1] = 8;

    vm.execute(instr);

    ASSERT_EQ(16, vm.registers[R0]);
}

TEST(and_instr, and_two_registers) {
    vm_t vm{};

    const auto instr = instruction_builder_t{}
        .binary_and()
        .destination_register(R0)
        .source_register_1(R1)
        .source_register_2(R2)
        .build();

    vm.registers[R1] = 0xf0f0;
    vm.registers[R2] = 0x00f0;

    vm.execute(instr);

    ASSERT_EQ(0x00f0, vm.registers[R0]);
}

TEST(and_instr, and_immediate) {
    vm_t vm{};

    const auto instr = instruction_builder_t{}
        .binary_and()
        .destination_register(R0)
        .source_register_1(R1)
        .immediate(0xE)
        .build();

    vm.registers[R1] = 0xf0fa;

    vm.execute(instr);

    ASSERT_EQ(0xa, vm.registers[R0]);
}