#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <concepts>
#include <limits>

namespace lc3
{

namespace vm
{
 
constexpr uint16_t opcode(uint16_t word) {
    return word >> 12;
}

constexpr bool use_immediate(uint16_t word) {
    return word & 0x0020;
}

constexpr uint16_t destination_register(uint16_t word) {
    return (word>>9) & 7;
}

constexpr uint16_t source_register_1(uint16_t word) {
    return (word>>6) & 7;
}

constexpr uint16_t source_register_2(uint16_t word) {
    return word & 7;
}

constexpr auto sign_extend(std::integral auto word, std::integral auto bit) -> decltype(word) {
    const bool is_negativ = (word>>bit) & 1;

    if (is_negativ)
        return word | (std::numeric_limits<decltype(word)>::max()<<bit);

    return word;
}

constexpr uint16_t immediate(uint16_t word) {
    return sign_extend(word & 0x1f, 4);
}

constexpr uint16_t offset(uint16_t word) {
    return sign_extend(word & 0x01ff, 8);
}

} // end namespace vm

} // end namespace lc3

#endif
