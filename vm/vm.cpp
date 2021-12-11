#include "vm.hpp"

#include <algorithm>
#include <iterator>

namespace lc3
{

namespace vm
{

namespace /* implementation */ { 

constexpr flags_t condition_flag(uint16_t value) {
    if (value == 0) {
        return flags_t::Zero;
    }
    else if (value >> 15) {
        return flags_t::Negative;
    }

    return flags_t::Positive;
}

void set_condition_flags(registers_t &registers, register_t index) {
    const auto flag = condition_flag(registers[index]);
    registers[CND] = flag;
}

void nop(vm_t&, uint16_t) {}

void add_instruction(vm_t& vm, uint16_t word) {
    const auto destination = destination_register(word);
    const auto sr1 = source_register_1(word);
    const auto x = vm.registers[sr1];

    if (use_immediate(word))
    {
        vm.registers[destination] = x + immediate(word);
    }
    else
    {
        vm.registers[destination] = x + vm.registers[source_register_2(word)];
    }

    set_condition_flags(vm.registers, static_cast<register_t>(destination));
}

void ld(vm_t& vm, uint16_t word) {
    const auto destination = destination_register(word);
    const auto pc = vm.registers[PC];
    vm.registers[destination] = vm.memory[pc + offset(word)];
}

void and_instruction(vm_t& vm, uint16_t word) {
    const auto destination = destination_register(word);
    const auto sr1 = source_register_1(word);
    const auto x = vm.registers[sr1];

    if (use_immediate(word))
    {
        vm.registers[destination] = x & immediate(word);
    }
    else
    {
        vm.registers[destination] = x & vm.registers[source_register_2(word)];
    }

    set_condition_flags(vm.registers, static_cast<register_t>(destination));
}

using opcode_handler_t = void (*)(vm_t&, uint16_t);

const opcode_handler_t opcode_handlers[] = {
    nop,
    add_instruction,
    nop,
    ld,
    nop,
    and_instruction
};

} // implementation namespace

void vm_t::load(std::span<uint16_t> bytecode, uint16_t address) {
    std::copy(std::begin(bytecode), std::end(bytecode), &memory[address]);
}

void vm_t::execute(uint16_t word) {
    const auto op{opcode(word)};
    const auto fn = opcode_handlers[op];
    fn(*this, word);
}

} // end namespace vm

} // end namespace lc3
