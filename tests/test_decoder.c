#include <core/hw/cpu/cpu.h>
#include <core/hw/memory/memory.h>
#include <core/hw/cpu/decoder.h>
#include <common/ester.h>

static const orca_logger_t decoder = {
    .ctx = "Decoder",
    .filename = "decoder.txt"
};

int main (void)
{
    orca_cpu_t cpu = {0};

    memory_init(&cpu.memory);
    orca_setup_bats(&cpu);
    cpu.msr[ORCA_MSR_IR] = true;
    cpu.msr[ORCA_MSR_DR] = true;

    orca_write32(&cpu.memory, 0, 0x38630001); /* addi r3, r3, 1 at physical 0 */
    cpu.pc = 0x80000000;

    uint32_t instruction = 0;
    int r = orca_fetch_instruction(&cpu, &instruction);
    if (r != 0)
    {
        ORCA_LOG_INFO(decoder, "fetch failed, r=%d", r);
        return 1;
    }

    ORCA_LOG_INFO(decoder, "instruction=0x%08X", instruction);

    return 0;
}
