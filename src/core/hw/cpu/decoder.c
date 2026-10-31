#include <core/hw/cpu/decoder.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <common/ester.h>
#include <core/hw/memory/memory.h>

int orca_op_unimplemented(orca_cpu_t *cpu,uint32_t instruction);
static const orca_logger_t decoder = {
    .ctx = "Decoder",
    .filename = "decoder.txt"
};

const orca_op_cell_t primary_opcode_table[] = {
    /* 0x00 */ { NULL,orca_op_unimplemented},
    /* 0x01 */ { NULL,orca_op_unimplemented},
    /* 0x02 */ { NULL,orca_op_unimplemented},
    /* 0x03 */ { "twi",orca_op_unimplemented},
    /* 0x04 */ { NULL,orca_op_unimplemented},
    /* 0x05 */ { NULL,orca_op_unimplemented},
    /* 0x06 */ { NULL,orca_op_unimplemented},
    /* 0x07 */ { "mulli",orca_op_unimplemented},
    /* 0x08 */ { "subfic",orca_op_unimplemented},
    /* 0x09 */ { NULL,orca_op_unimplemented},
    /* 0x0A */ { "cmpli",orca_op_unimplemented},
    /* 0x0B */ { "cmpi",orca_op_unimplemented},
    /* 0x0C */ { "addic",orca_op_unimplemented},
    /* 0x0D */ { "addic.",orca_op_unimplemented},
    /* 0x0E */ { "addi",orca_op_unimplemented},
    /* 0x0F */ { "addis",orca_op_unimplemented},
    /* 0x10 */ { "bc",orca_op_unimplemented},
    /* 0x11 */ { "sc",orca_op_unimplemented},
    /* 0x12 */ { "b",orca_op_unimplemented},
    /* 0x13 */ { NULL,orca_op_unimplemented},
    /* 0x14 */ { "rlwimi",orca_op_unimplemented},
    /* 0x15 */ { "rlwinm",orca_op_unimplemented},
    /* 0x16 */ { NULL,orca_op_unimplemented},
    /* 0x17 */ { "rlwnm",orca_op_unimplemented},
    /* 0x18 */ { "ori",orca_op_unimplemented},
    /* 0x19 */ { "oris",orca_op_unimplemented},
    /* 0x1A */ { "xori",orca_op_unimplemented},
    /* 0x1B */ { "xoris",orca_op_unimplemented},
    /* 0x1C */ { "andi.",orca_op_unimplemented},
    /* 0x1D */ { "andis.",orca_op_unimplemented},
    /* 0x1E */ { NULL,orca_op_unimplemented},
    /* 0x1F */ { NULL,orca_op_unimplemented},
    /* 0x20 */ { "lwz",orca_op_unimplemented},
    /* 0x21 */ { "lwzu",orca_op_unimplemented},
    /* 0x22 */ { "lbz",orca_op_unimplemented},
    /* 0x23 */ { "lbzu",orca_op_unimplemented},
    /* 0x24 */ { "stw",orca_op_unimplemented},
    /* 0x25 */ { "stwu",orca_op_unimplemented},
    /* 0x26 */ { "stb",orca_op_unimplemented},
    /* 0x27 */ { "stbu",orca_op_unimplemented},
    /* 0x28 */ { "lhz",orca_op_unimplemented},
    /* 0x29 */ { "lhzu",orca_op_unimplemented},
    /* 0x2A */ { "lha",orca_op_unimplemented},
    /* 0x2B */ { "lhau",orca_op_unimplemented},
    /* 0x2C */ { "sth",orca_op_unimplemented},
    /* 0x2D */ { "sthu",orca_op_unimplemented},
    /* 0x2E */ { "lmw",orca_op_unimplemented},
    /* 0x2F */ { "stmw",orca_op_unimplemented},
    /* 0x30 */ { "lfs",orca_op_unimplemented},
    /* 0x31 */ { "lfsu",orca_op_unimplemented},
    /* 0x32 */ { "lfd",orca_op_unimplemented},
    /* 0x33 */ { "lfdu",orca_op_unimplemented},
    /* 0x34 */ { "stfs",orca_op_unimplemented},
    /* 0x35 */ { "stfsu",orca_op_unimplemented},
    /* 0x36 */ { "stfd",orca_op_unimplemented},
    /* 0x37 */ { "stfdu",orca_op_unimplemented},
    /* 0x38 */ { "psq_l",orca_op_unimplemented},
    /* 0x39 */ { "psq_lu",orca_op_unimplemented},
    /* 0x3A */ { NULL,orca_op_unimplemented},
    /* 0x3B */ { NULL,orca_op_unimplemented},
    /* 0x3C */ { "psq_st",orca_op_unimplemented},
    /* 0x3D */ { "psq_stu",orca_op_unimplemented},
    /* 0x3E */ { NULL,orca_op_unimplemented},
    /* 0x3F */ { NULL,orca_op_unimplemented},
};

const orca_op_cell_t orca_op31_table[] = {
 /* 0x000 */ [0x000] = {"cmp", orca_op_unimplemented},
 /* 0x004 */ [0x004] = {"tw", orca_op_unimplemented},
 /* 0x008 */ [0x008] = {"subfc", orca_op_unimplemented},
 /* 0x00A */ [0x00A] = {"addc", orca_op_unimplemented},
 /* 0x00B */ [0x00B] = {"mulhwu", orca_op_unimplemented},
 /* 0x013 */ [0x013] = {"mfcr", orca_op_unimplemented},
 /* 0x014 */ [0x014] = {"lwarx", orca_op_unimplemented},
 /* 0x017 */ [0x017] = {"lwzx", orca_op_unimplemented},
 /* 0x018 */ [0x018] = {"slw", orca_op_unimplemented},
 /* 0x01A */ [0x01A] = {"cntlzw", orca_op_unimplemented},
 /* 0x01C */ [0x01C] = {"and", orca_op_unimplemented},
 /* 0x020 */ [0x020] = {"cmpl", orca_op_unimplemented},
 /* 0x028 */ [0x028] = {"subf", orca_op_unimplemented},
 /* 0x036 */ [0x036] = {"dcbst", orca_op_unimplemented},
 /* 0x037 */ [0x037] = {"lwzux", orca_op_unimplemented},
 /* 0x03C */ [0x03C] = {"andc", orca_op_unimplemented},
 /* 0x04B */ [0x04B] = {"mulhw", orca_op_unimplemented},
 /* 0x053 */ [0x053] = {"mfmsr", orca_op_unimplemented},
 /* 0x056 */ [0x056] = {"dcbf", orca_op_unimplemented},
 /* 0x057 */ [0x057] = {"lbzx", orca_op_unimplemented},
 /* 0x068 */ [0x068] = {"neg", orca_op_unimplemented},
 /* 0x077 */ [0x077] = {"lbzux", orca_op_unimplemented},
 /* 0x07C */ [0x07C] = {"nor", orca_op_unimplemented},
 /* 0x088 */ [0x088] = {"subfe", orca_op_unimplemented},
 /* 0x08A */ [0x08A] = {"adde", orca_op_unimplemented},
 /* 0x090 */ [0x090] = {"mtcrf", orca_op_unimplemented},
 /* 0x092 */ [0x092] = {"mtmsr", orca_op_unimplemented},
 /* 0x096 */ [0x096] = {"stwcx.", orca_op_unimplemented},
 /* 0x097 */ [0x097] = {"stwx", orca_op_unimplemented},
 /* 0x0B7 */ [0x0B7] = {"stwux", orca_op_unimplemented},
 /* 0x0C8 */ [0x0C8] = {"subfze", orca_op_unimplemented},
 /* 0x0CA */ [0x0CA] = {"addze", orca_op_unimplemented},
 /* 0x0D2 */ [0x0D2] = {"mtsr", orca_op_unimplemented},
 /* 0x0D7 */ [0x0D7] = {"stbx", orca_op_unimplemented},
 /* 0x0E8 */ [0x0E8] = {"subfme", orca_op_unimplemented},
 /* 0x0EA */ [0x0EA] = {"addme", orca_op_unimplemented},
 /* 0x0EB */ [0x0EB] = {"mullw", orca_op_unimplemented},
 /* 0x0F2 */ [0x0F2] = {"mtsrin", orca_op_unimplemented},
 /* 0x0F6 */ [0x0F6] = {"dcbtst", orca_op_unimplemented},
 /* 0x0F7 */ [0x0F7] = {"stbux", orca_op_unimplemented},
 /* 0x10A */ [0x10A] = {"add", orca_op_unimplemented},
 /* 0x116 */ [0x116] = {"dcbt", orca_op_unimplemented},
 /* 0x117 */ [0x117] = {"lhzx", orca_op_unimplemented},
 /* 0x11C */ [0x11C] = {"eqv", orca_op_unimplemented},
 /* 0x132 */ [0x132] = {"tlbie", orca_op_unimplemented},
 /* 0x136 */ [0x136] = {"eciwx", orca_op_unimplemented},
 /* 0x137 */ [0x137] = {"lhzux", orca_op_unimplemented},
 /* 0x13C */ [0x13C] = {"xor", orca_op_unimplemented},
 /* 0x153 */ [0x153] = {"mfspr", orca_op_unimplemented},
 /* 0x157 */ [0x157] = {"lhax", orca_op_unimplemented},
 /* 0x172 */ [0x172] = {"tlbia", orca_op_unimplemented},
 /* 0x173 */ [0x173] = {"mftb", orca_op_unimplemented},
 /* 0x177 */ [0x177] = {"lhaux", orca_op_unimplemented},
 /* 0x197 */ [0x197] = {"sthx", orca_op_unimplemented},
 /* 0x19C */ [0x19C] = {"orc", orca_op_unimplemented},
 /* 0x1B6 */ [0x1B6] = {"ecowx", orca_op_unimplemented},
 /* 0x1B7 */ [0x1B7] = {"sthux", orca_op_unimplemented},
 /* 0x1BC */ [0x1BC] = {"or", orca_op_unimplemented},
 /* 0x1CB */ [0x1CB] = {"divwu", orca_op_unimplemented},
 /* 0x1D3 */ [0x1D3] = {"mtspr", orca_op_unimplemented},
 /* 0x1D6 */ [0x1D6] = {"dcbi", orca_op_unimplemented},
 /* 0x1DC */ [0x1DC] = {"nand", orca_op_unimplemented},
 /* 0x1EB */ [0x1EB] = {"divw", orca_op_unimplemented},
 /* 0x200 */ [0x200] = {"mcrxr", orca_op_unimplemented},
 /* 0x215 */ [0x215] = {"lswx", orca_op_unimplemented},
 /* 0x216 */ [0x216] = {"lwbrx", orca_op_unimplemented},
 /* 0x217 */ [0x217] = {"lfsx", orca_op_unimplemented},
 /* 0x218 */ [0x218] = {"srw", orca_op_unimplemented},
 /* 0x236 */ [0x236] = {"tlbsync", orca_op_unimplemented},
 /* 0x237 */ [0x237] = {"lfsux", orca_op_unimplemented},
 /* 0x253 */ [0x253] = {"mfsr", orca_op_unimplemented},
 /* 0x255 */ [0x255] = {"lswi", orca_op_unimplemented},
 /* 0x256 */ [0x256] = {"sync", orca_op_unimplemented},
 /* 0x257 */ [0x257] = {"lfdx", orca_op_unimplemented},
 /* 0x277 */ [0x277] = {"lfdux", orca_op_unimplemented},
 /* 0x293 */ [0x293] = {"mfsrin", orca_op_unimplemented},
 /* 0x295 */ [0x295] = {"stswx", orca_op_unimplemented},
 /* 0x296 */ [0x296] = {"stwbrx", orca_op_unimplemented},
 /* 0x297 */ [0x297] = {"stfsx", orca_op_unimplemented},
 /* 0x2B7 */ [0x2B7] = {"stfsux", orca_op_unimplemented},
 /* 0x2D5 */ [0x2D5] = {"stswi", orca_op_unimplemented},
 /* 0x2D7 */ [0x2D7] = {"stfdx", orca_op_unimplemented},
 /* 0x2F6 */ [0x2F6] = {"dcba", orca_op_unimplemented},
 /* 0x2F7 */ [0x2F7] = {"stfdux", orca_op_unimplemented},
 /* 0x316 */ [0x316] = {"lhbrx", orca_op_unimplemented},
 /* 0x318 */ [0x318] = {"sraw", orca_op_unimplemented},
 /* 0x338 */ [0x338] = {"srawi", orca_op_unimplemented},
 /* 0x356 */ [0x356] = {"eieio", orca_op_unimplemented},
 /* 0x396 */ [0x396] = {"sthbrx", orca_op_unimplemented},
 /* 0x39A */ [0x39A] = {"extsh", orca_op_unimplemented},
 /* 0x3BA */ [0x3BA] = {"extsb", orca_op_unimplemented},
 /* 0x3D6 */ [0x3D6] = {"icbi", orca_op_unimplemented},
 /* 0x3D7 */ [0x3D7] = {"stfiwx", orca_op_unimplemented},
 /* 0x3F6 */ [0x3F6] = {"dcbz", orca_op_unimplemented}
};

const orca_op_cell_t orca_op63_table[] = {
 /* 0x000 */ [0x000] = {"fcmpu", orca_op_unimplemented},
 /* 0x00C */ [0x00C] = {"frsp", orca_op_unimplemented},
 /* 0x00E */ [0x00E] = {"fctiw", orca_op_unimplemented},
 /* 0x00F */ [0x00F] = {"fctiwz", orca_op_unimplemented},
 /* 0x012 */ [0x012] = {"fdiv", orca_op_unimplemented},
 /* 0x014 */ [0x014] = {"fsub", orca_op_unimplemented},
 /* 0x015 */ [0x015] = {"fadd", orca_op_unimplemented},
 /* 0x016 */ [0x016] = {"fsqrt", orca_op_unimplemented},
 /* 0x017 */ [0x017] = {"fsel", orca_op_unimplemented},
 /* 0x019 */ [0x019] = {"fmul", orca_op_unimplemented},
 /* 0x01A */ [0x01A] = {"frsqrte", orca_op_unimplemented},
 /* 0x01C */ [0x01C] = {"fmsub", orca_op_unimplemented},
 /* 0x01D */ [0x01D] = {"fmadd", orca_op_unimplemented},
 /* 0x01E */ [0x01E] = {"fnmsub", orca_op_unimplemented},
 /* 0x01F */ [0x01F] = {"fnmadd", orca_op_unimplemented},
 /* 0x020 */ [0x020] = {"fcmpo", orca_op_unimplemented},
 /* 0x026 */ [0x026] = {"mtfsb1", orca_op_unimplemented},
 /* 0x028 */ [0x028] = {"fneg", orca_op_unimplemented},
 /* 0x040 */ [0x040] = {"mcrfs", orca_op_unimplemented},
 /* 0x046 */ [0x046] = {"mtfsb0", orca_op_unimplemented},
 /* 0x048 */ [0x048] = {"fmr", orca_op_unimplemented},
 /* 0x086 */ [0x086] = {"mtfsfi", orca_op_unimplemented},
 /* 0x088 */ [0x088] = {"fnabs", orca_op_unimplemented},
 /* 0x108 */ [0x108] = {"fabs", orca_op_unimplemented},
 /* 0x247 */ [0x247] = {"mffs", orca_op_unimplemented},
 /* 0x2C7 */ [0x2C7] = {"mtfsf", orca_op_unimplemented}
};

const orca_op_cell_t orca_op19_table[] = {
 /* 0x000 */ [0x000] = {"mcrf", orca_op_unimplemented},
 /* 0x010 */ [0x010] = {"bclr", orca_op_unimplemented},
 /* 0x021 */ [0x021] = {"crnor", orca_op_unimplemented},
 /* 0x032 */ [0x032] = {"rfi", orca_op_unimplemented},
 /* 0x081 */ [0x081] = {"crandc", orca_op_unimplemented},
 /* 0x096 */ [0x096] = {"isync", orca_op_unimplemented},
 /* 0x0C1 */ [0x0C1] = {"crxor", orca_op_unimplemented},
 /* 0x0E1 */ [0x0E1] = {"crnand", orca_op_unimplemented},
 /* 0x101 */ [0x101] = {"crand", orca_op_unimplemented},
 /* 0x121 */ [0x121] = {"creqv", orca_op_unimplemented},
 /* 0x1A1 */ [0x1A1] = {"crorc", orca_op_unimplemented},
 /* 0x1C1 */ [0x1C1] = {"cror", orca_op_unimplemented},
 /* 0x210 */ [0x210] = {"bcctr", orca_op_unimplemented}
};

const orca_op_cell_t orca_op59_table[] = {
 /* 0x012 */ [0x012] = {"fdivs", orca_op_unimplemented},
 /* 0x014 */ [0x014] = {"fsubs", orca_op_unimplemented},
 /* 0x015 */ [0x015] = {"fadds", orca_op_unimplemented},
 /* 0x016 */ [0x016] = {"fsqrts", orca_op_unimplemented},
 /* 0x018 */ [0x018] = {"fres", orca_op_unimplemented},
 /* 0x019 */ [0x019] = {"fmuls", orca_op_unimplemented},
 /* 0x01C */ [0x01C] = {"fmsubs", orca_op_unimplemented},
 /* 0x01D */ [0x01D] = {"fmadds", orca_op_unimplemented},
 /* 0x01E */ [0x01E] = {"fnmsubs", orca_op_unimplemented},
 /* 0x01F */ [0x01F] = {"fnmadds", orca_op_unimplemented}
};

static int
orca_lookup_table(uint32_t instruction,const orca_op_cell_t **table)
{

    uint32_t primary = ORCA_PRIMARY_OPCODE(instruction);

    /* Common primary codes repeeted alot so check it first */
    switch (primary)
    {
        case 19u:
        {
            *table = orca_op19_table;
        }
        break;

        case 31u:
        {
            *table = orca_op31_table;
        }
        break;

        case 59u:
        {
            *table = orca_op59_table;
        }
        break;

        case 63u:
        {
            *table = orca_op63_table;
        }
        break;

        default: *table = primary_opcode_table;
    }

    return 0;
}

int orca_fetch_instruction(orca_cpu_t *cpu,uint32_t *instruction_out)
{
    uint32_t paddr;

    if (cpu == NULL)
    {
        return -1;
    }

    orca_translate(cpu, cpu->pc, &paddr, true);
    orca_read32(&cpu->memory, paddr,instruction_out);

    return 0;
}

int
orca_cpu_decode(orca_cpu_t *cpu, uint32_t instruction, orca_cpu_operation *operation_out)
{

    if (cpu == NULL)
    {
        return -1;
    }

    const orca_op_cell_t *table;
    orca_cpu_operation operation;

    (void)orca_lookup_table(instruction, &table);

    if (table == primary_opcode_table)
    {
        const size_t primary = ORCA_PRIMARY_OPCODE(instruction);
        operation = primary_opcode_table[primary].operation;
    }else
    {
        const size_t extended_opcode = ORCA_EXTENDED_OPCODE(instruction);
        operation = table[extended_opcode].operation;
    }

    *operation_out = operation;
    return 0;
}

int orca_op_unimplemented(orca_cpu_t *cpu,uint32_t instruction)
{
    (void)cpu;
    const orca_op_cell_t *table;
    orca_lookup_table(instruction,&table);
    const char *instruction_name;

    if (table == primary_opcode_table)
    {
        uint32_t primary_opcode = ORCA_PRIMARY_OPCODE(instruction);
        instruction_name = table[primary_opcode].name;
    }else
    {
        uint32_t extended_opcode = ORCA_EXTENDED_OPCODE(instruction);
        instruction_name = table[extended_opcode].name;
    }

    ORCA_ABORT(decoder,"Unimplemented instruction %s 0x%08X",
                instruction_name,instruction);
    return 0;
}
