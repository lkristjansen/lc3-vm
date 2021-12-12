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

void nop(memory_t&, registers_t&, uint16_t) {}

void add_instruction(memory_t&, registers_t& registers, uint16_t word) {
    const auto destination = destination_register(word);
    const auto sr1 = source_register_1(word);
    const auto x = registers[sr1];

    if (use_immediate(word))
    {
        registers[destination] = x + immediate(word);
    }
    else
    {
        registers[destination] = x + registers[source_register_2(word)];
    }

    set_condition_flags(registers, static_cast<register_t>(destination));
}

void ld(memory_t& memory, registers_t& registers, uint16_t word) {
    const auto destination = destination_register(word);
    const auto pc = registers[PC];
    const auto pc_offset = offset(word);
    const auto addr = static_cast<uint16_t>(pc + pc_offset);
    registers[destination] = memory[addr];
}

void and_instruction(memory_t&, registers_t& registers, uint16_t word) {
    const auto destination = destination_register(word);
    const auto sr1 = source_register_1(word);
    const auto x = registers[sr1];

    if (use_immediate(word))
    {
        registers[destination] = x & immediate(word);
    }
    else
    {
        registers[destination] = x & registers[source_register_2(word)];
    }

    set_condition_flags(registers, static_cast<register_t>(destination));
}

using opcode_handler_t = void (*)(memory_t&, registers_t&, uint16_t);

const opcode_handler_t opcode_handlers[] = {
    nop,
    add_instruction,
    nop,
    ld,
    nop,
    and_instruction
};

} // implementation namespace

void load(memory_t& memory, std::span<uint16_t> bytecode, uint16_t address) {
    std::copy(std::begin(bytecode), std::end(bytecode), &memory[address]);
}

void execute(memory_t& memory, registers_t& registers, uint16_t word) {
    const auto op{opcode(word)};
    const auto fn = opcode_handlers[op];
    fn(memory, registers, word);
}

} // end namespace vm

} // end namespace lc3
