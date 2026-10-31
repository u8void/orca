add_library(orca_core STATIC
    common/ester.c
    core/hw/memory/memory.c
    core/hw/cpu/decoder.c
    core/hw/cpu/cpu.c
)

target_include_directories(orca_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_executable(orca
    ${PROJECT_SOURCE_DIR}/src/main.c
)

target_link_libraries(orca PRIVATE
    orca_core
)
