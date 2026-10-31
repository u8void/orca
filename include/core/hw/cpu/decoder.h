#include <stdint.h>
#include"cpu.h"

/* Extract specific bit*/
#define ORCA_REGISTER_BIT(register,bit) (((register) >> (31u - (bit))) & 1u)

/* Extract the primary opcode first 6-bits which determine the operation*/
#define ORCA_PRIMARY_OPCODE(instruction) ((instruction) >> 26)

/* Extract the extended opcode which determine the operation if multi
 * instruction share same primary opcode */
#define ORCA_EXTENDED_OPCODE(instruction) (((instruction) >> 1) & 0x3FF)

/* An operation handler Based on what operation we got from op table*/
typedef int(*orca_cpu_operation)(orca_cpu_t *cpu, uint32_t instruction) ;

typedef struct
{
    const char *name;
    orca_cpu_operation operation;
}orca_op_cell_t;

int orca_fetch_instruction(orca_cpu_t *cpu,uint32_t *instruction_out);
int
orca_cpu_decode(orca_cpu_t *cpu, uint32_t instruction, orca_cpu_operation *operation_out);
int orca_cpu_exec(orca_cpu_t *cpu,uint32_t instruction,orca_cpu_operation op);
