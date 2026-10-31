#include <core/hw/cpu/cpu.h>
#include <stdbool.h>

/* Hard reset configration */
int orca_cpu_init(orca_cpu_t *cpu)
{
    cpu->fpscr = 0u;
    cpu->cr.cr0 = 0u;
    cpu->cr.cr1 = 0u;
    cpu->cr.cr2 = 0u;
    cpu->cr.cr3 = 0u;
    cpu->cr.cr4 = 0u;
    cpu->cr.cr5 = 0u;
    cpu->cr.cr6 = 0u;
    cpu->cr.cr7 = 0u;
    cpu->msr[31] = true;
    cpu->msr[18] = true;
    cpu->msr[30] = true;
    cpu->msr[26] = true;
    cpu->msr[ORCA_MSR_IR] = true;
    cpu->msr[ORCA_MSR_DR] = true;
    cpu->dec = 0xFFFFFFFF;
    return 0;
}
