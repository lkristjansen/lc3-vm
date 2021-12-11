#pragma once

#include "vm/vm.hpp"

#include <cstdint>

namespace lc3
{

namespace test
{

struct instruction_builder_t {
    uint16_t word;

    constexpr uint16_t build() {
        return word;
    }

    constexpr instruction_builder_t& add() {
        word |= 0x1000;
        return *this; 
    }

    constexpr instruction_builder_t& ld() {
        word |= 0x3000;
        return *this;
    }

    constexpr instruction_builder_t& binary_and() {
        word |= 0x5000;
        return *this;
    }

    constexpr instruction_builder_t& source_register_1(vm::register_t reg) {
        word |= static_cast<uint16_t>(reg) << 6;
        return *this;
    }

    constexpr instruction_builder_t& source_register_2(vm::register_t reg) {
        word |= static_cast<uint16_t>(reg);
        return *this;
    }

    constexpr instruction_builder_t& destination_register(vm::register_t reg) {
        word |= static_cast<uint16_t>(reg) << 9;
        return *this;
    }

    constexpr instruction_builder_t& immediate(uint16_t value) {
        word |= 0x20;
        word |= value;
        return *this;
    }
};



} // end namespace test

} // end namespace lc3
