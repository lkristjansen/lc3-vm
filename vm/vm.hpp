#pragma once

#ifndef VM_HPP
#define VM_HPP

#include <cstdint>
#include <limits>
#include <array>
#include <span>

#include "opcode.hpp"

namespace lc3
{

namespace vm
{

enum register_t {
    R0 = 0, R1, R2, R3, R4, R5, R6, R7, PC, CND, CNT
};

enum flags_t {
    Positive,
    Zero,
    Negative,
};

using registers_t = std::array<uint16_t, register_t::CNT>;

using memory_t = std::array<uint16_t, std::numeric_limits<uint16_t>::max()>;

void load(memory_t& memory, std::span<uint16_t> bytecode, uint16_t address);

void execute(memory_t& memory, registers_t& registers, uint16_t word);

} // end namespace vm

} // end namespace lc3

#endif // VM_HPP
