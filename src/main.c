#include <core/hw/cpu/cpu.h>
#include <core/hw/memory/memory.h>
#include <core/hw/cpu/decoder.h>
#include <common/ester.h>

static const orca_logger_t orca = {
    .ctx = "orca",
    .filename = "orca.txt"
};

int main (void)
{
    orca_cpu_t cpu = {0};
    orca_cpu_init(&cpu);
    memory_init(&cpu.memory);
    orca_setup_bats(&cpu);
    return 0;
}
