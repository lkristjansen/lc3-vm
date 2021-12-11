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
    R0 = 0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    PC,
    CND,
    CNT
};

using registers_t = std::array<uint16_t, static_cast<std::size_t>(register_t::CNT)>;

enum flags_t {
    Positive,
    Zero,
    Negative,
};

constexpr flags_t condition_flag(uint16_t value) {
    if (value == 0) {
        return flags_t::Zero;
    }
    else if (value >> 15) {
        return flags_t::Negative;
    }

    return flags_t::Positive;
}

void set_condition_flags(registers_t &registers, register_t index);

using memory_t = std::array<uint16_t, std::numeric_limits<uint16_t>::max()>;

struct vm_t
{
    memory_t memory{};
    registers_t registers{};

    /// TODO: handle out of bounds errors.
    void load(std::span<uint16_t> bytecode, uint16_t address);
};

void add(vm_t& vm, uint16_t instruction);

} // end namespace vm

} // end namespace lc3

#endif // VM_HPP
