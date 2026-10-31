#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct orca_cpu orca_cpu_t;

#define ORCA_RAM_SIZE (24 *1024 *1024) /* 24MB */

#define PHYSICAL_RAM_START 0x00000000
#define PHYSICAL_RAM_END 0x017fffff

#define LOGICAL_CACHED_RAM_START 0x80000000
#define LOGICAL_CHACHED_RAM_END 0x817fffff

#define LOGICAL_NOT_CACHED_RAM_START 0xC0000000
#define LOGICAL_NOT_CHACHED_RAM_END 0xC17fffff

#define L2_CACHE_START 0xe0000000
#define L2_CACHE_END 0xe0003fff

#define ORCA_MSR_IR 26
#define ORCA_MSR_DR 27

#define L2_CACHE_SIZE (16 *1024)

typedef struct
{
    uint8_t *ram;
}orca_memory_t;

int memory_init(orca_memory_t *mem);

int
orca_translate(orca_cpu_t *cpu,
               uint32_t effective_addr,
               uint32_t *physical_addr,
               bool fetch);

int orca_write32(orca_memory_t *memory,
                 uint32_t paddr,
                 uint32_t value);

int orca_read32(orca_memory_t *memory,
                uint32_t paddr,
                uint32_t *value_out);

int orca_setup_bats(orca_cpu_t *cpu);
