#include <stdlib.h>
#include <stdint.h>
#include <core/hw/memory/memory.h>
#include <core/hw/cpu/cpu.h>

int memory_init(orca_memory_t *mem)
{
    mem->ram = (uint8_t*)malloc(ORCA_RAM_SIZE);
    return 0;
}

int orca_setup_bats(orca_cpu_t *cpu)
{

    if (cpu == NULL)
    {
        return -1;
    }

    /* from dolphin emu Source/Core/Core/Boot/Boot_BS2Emu.cpp:116 */
    cpu->ibat[0].effective_addr = 0x80000000;
    cpu->ibat[0].physical_addr = 0x00000000;
    cpu->ibat[0].size = 0x10000000u;
    cpu->ibat[0].cached = true;

    cpu->dbat[0].effective_addr = 0x80000000;
    cpu->dbat[0].physical_addr = 0x00000000;
    cpu->dbat[0].size = 0x10000000u;
    cpu->dbat[0].cached = true;

    cpu->dbat[1].effective_addr = 0xC0000000;
    cpu->dbat[1].physical_addr = 0x00000000;
    cpu->dbat[1].size = 0x10000000u;
    cpu->dbat[1].cached = false;

    return 0;
}

int
orca_translate(orca_cpu_t *cpu,
               uint32_t effective_addr,
               uint32_t *physical_addr,
               bool fetch)
{

    if (cpu == NULL)
    {
        return -1;
    }

    const orca_bat_t *bank = fetch ? cpu->ibat : cpu->dbat;
    const int32_t msr_bit = fetch ? ORCA_MSR_IR : ORCA_MSR_DR;

    if (cpu->msr[msr_bit] == false)
    {
        *physical_addr = effective_addr;
        return 1;
    }

    uint32_t offset;
    /* Gamecube use 0,1 bancks only*/
    for (int i = 0 ; i < 2 ; i++)
    {
        offset = effective_addr - bank[i].effective_addr;

        if (offset < bank[i].size/*256MB*/)
        {
            *physical_addr = bank[i].physical_addr + offset;
            return 0;
        }
    }

    return -1;
}

int orca_read32(orca_memory_t *memory,
                uint32_t paddr,
                uint32_t *value_out)
{
    if (memory == NULL || memory->ram == NULL || value_out == NULL)
        return -1;

    if (paddr > ORCA_RAM_SIZE - 4)
        return -1;

    *value_out =
    ((uint32_t)memory->ram[paddr]     << 24) |
    ((uint32_t)memory->ram[paddr + 1] << 16) |
    ((uint32_t)memory->ram[paddr + 2] << 8)  |
    ((uint32_t)memory->ram[paddr + 3]);

    return 0;
}

int orca_write32(orca_memory_t *memory,
                 uint32_t paddr,
                 uint32_t value)
{
    if (memory == NULL || memory->ram == NULL)
        return -1;

    if (paddr > ORCA_RAM_SIZE - 4)
        return -1;

    memory->ram[paddr]     = (value >> 24) & 0xFF;
    memory->ram[paddr + 1] = (value >> 16) & 0xFF;
    memory->ram[paddr + 2] = (value >> 8) & 0xFF;
    memory->ram[paddr + 3] = value & 0xFF;

    return 0;
}
