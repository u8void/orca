cmake_minimum_required(VERSION 3.10)

project(orca LANGUAGES C
  VERSION 0.1.0
  DESCRIPTION "GameCube emulator")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are not supported. Use: cmake -S . -B build")
endif()

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wstrict-prototypes
    -Wold-style-definition
    -Wmissing-prototypes
    -Wmissing-declarations
    -Wcast-qual
    -Wcast-align
    -Wwrite-strings
    -Wpointer-arith
    -Wfloat-equal
    -Wundef
    -Wswitch-enum
    -Wswitch-default
    -Wvla
    -Wredundant-decls
    -Wformat=2
    -Wformat-security
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wstrict-aliasing=3
    -Wformat-overflow=2
    -Wformat-truncation=2
    -Warray-bounds=2
    -Wstringop-overflow=4
    -Wshift-overflow=2
    -Wshift-count-overflow
    -Wshift-negative-value
    -Wlogical-op
    -Wduplicated-cond
    -Wduplicated-branches
    -Wmisleading-indentation
    -Wmissing-field-initializers
    -fanalyzer
    -Wanalyzer-too-complex
)

add_subdirectory(src)
add_subdirectory(tests)
