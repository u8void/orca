#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "../memory/memory.h"

/*
 * A condition register (CR) is a 32-bit register that is divided into eight
 * 4-bit fields,CR0–CR7. This register stores the results of certain arithmetic
 * operations and provides a mechanism for testing and branching.
 */

#define ORCA_CR_BIT(cr_field,bit) ((((cr_field) >> (3 - (bit))) & 1u))
typedef struct
{
    uint8_t cr0 : 4;
    uint8_t cr1 : 4;
    uint8_t cr2 : 4;
    uint8_t cr3 : 4;
    uint8_t cr4 : 4;
    uint8_t cr5 : 4;
    uint8_t cr6 : 4;
    uint8_t cr7 : 4;
}orca_cr_register_t;

typedef struct
{
    uint32_t upper;
    uint32_t lower;
}oorca_tp_register_t;

/*              Memory Management Registers             */
/* isntead of 2 separate uint32_t treat BATU and BATL as one block */
typedef struct
{
    uint32_t effective_addr; /* BEPI */
    uint32_t physical_addr; /* BRPN */
    size_t size;
    bool cached;
}orca_bat_t;

#define ORCA_MSR_IR 26
#define ORCA_MSR_DR 27

typedef struct orca_cpu
{
    /* program counter */
    uint32_t pc;

/*              USER MODEL UISA             */
    /* General-purpose registers */
    uint32_t gpr[32];

    /* Floating-point registers */
    double fpr[32];

    /* floating-point status and control register */
    float fpscr;

    /* integer exception register */
    uint32_t xer;

    /* Count register */
    uint32_t ctr;

    /* Decrementer register */
    uint32_t dec;

    /* Link register */
    uint32_t lr;

    /* condition register */
    orca_cr_register_t cr;

    /* performance monitors registers*/
    uint32_t upmc[4];

    /* monitor control */
    uint32_t ummcr[2];

    /* User Sampled Instruction Address Register */
    uint32_t usia;


/*              USER MODEL—VEA              */
    /* Time Base Facility */
    /* handle read and write */
    oorca_tp_register_t tp;

    /* Graphics Quantization Registers */
    uint32_t gqr[8];

/*              Performance Monitor Registers               */
    /* Performance Counters */
    uint32_t pmc[4];

    /* Sampled Instruction Address Register */
    uint32_t sia;

    /* Monitor Control */
    uint32_t mmcr[2];

/*              Configuration Registers             */
    /* Hardware Implementation Registers */
    uint32_t hid[3];
    uint32_t tbr269;

    /* Processor Version Register */
    uint32_t pvr;

    /* Machine state register */
    bool msr[32];

    /* Instruction BAT Registers */
    orca_bat_t ibat[4];

    /* Data BAT Registers */
    orca_bat_t dbat[4];

    /* Segment Register */
    uint32_t sr[16];

    /* specifies the variables used in accessing the page tables in memory */
    uint32_t sdr;

/*              Exception Handling Registers                */
    /* sprgs */
    uint32_t sprg[4];

    /* Data Address Register */
    uint32_t dar;

    /* defines the cause of data access and alignment exceptions */
    uint32_t dsisr;

    /* Save and Restore Registers */
    uint32_t spr[2];

/*              Miscellaneous Register              */
    /* External Access Register */
    uint32_t ear;

    /* Data Address Breakpoint Register */
    uint32_t dabr;

    /* Write Gather Pipe Pipe */
    uint32_t wpar;

    /* L2 Control Register */
    uint32_t l2cr;

    /* Direct Memory Access */
    uint32_t dmal;
    uint32_t dmau;

/*              Power/Thermal Management Registers              */
    /*Thermal Assist Unit Registers */
    uint32_t thrm[4];

    /* Instruction Cache Throttling Control Register */
    uint32_t ictc;

    orca_memory_t memory;
}orca_cpu_t;

int orca_cpu_init(orca_cpu_t *cpu);
