cmake_minimum_required(VERSION 3.22)

project(
    lc3-vm
    VERSION 1.0
    DESCRIPTION "16bit Virtual Machine follow the LC-3 specification"
    LANGUAGES CXX)

add_library(
    vm
    STATIC
    vm/opcode.cpp
    vm/opcode.hpp
    vm/vm.cpp
    vm/vm.hpp)

target_compile_features(vm PUBLIC cxx_std_20)

target_compile_options(vm PRIVATE -Wall -Wextra)

set_target_properties(vm PROPERTIES CXX_EXTENSIONS OFF)

enable_testing()

find_package(GTest REQUIRED)

add_executable(
    vm_tests
    test/test_opcode.cpp
    test/test_vm.cpp
    test/instruction_builder.hpp)

target_link_libraries(vm_tests PRIVATE GTest::gtest GTest::gtest_main vm)

target_include_directories(vm_tests PRIVATE ${PROJECT_SOURCE_DIR})

target_compile_features(vm_tests PRIVATE cxx_std_20)

set_target_properties(vm_tests PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(vm_tests PRIVATE -Wall -Wextra)

add_test(vm_tests vm_tests)
