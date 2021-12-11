#include "vm.hpp"

#include <algorithm>
#include <iterator>

namespace lc3
{

namespace vm
{

void set_condition_flags(registers_t &registers, register_t index) {
    const auto flag = condition_flag(registers[index]);
    registers[CND] = flag;
}

void vm_t::load(std::span<uint16_t> bytecode, uint16_t address) {
    std::copy(std::begin(bytecode), std::end(bytecode), &memory[address]);
}

void add(vm_t& vm, uint16_t instruction) {
    const auto destination = destination_register(instruction);
    const auto sr1 = source_register_1(instruction);
    const auto x = vm.registers[sr1];

    if (use_immediate(instruction))
    {
        vm.registers[destination] = x + immediate(instruction);
    }
    else
    {
        vm.registers[destination] = x + vm.registers[source_register_2(instruction)];
    }

    set_condition_flags(vm.registers, static_cast<register_t>(destination));
}

} // end namespace vm

} // end namespace lc3
