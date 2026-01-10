#include "./cpu.h"
#include "../log/log.h"
#include "./inst_table.c"

uint8_t gb_cpu_fetch8(GbCpuState *cpu)
{
    const uint8_t data = gb_mmu_read(cpu->mmu, cpu->regs.PC++);
    return data;
}

uint16_t gb_cpu_fetch16(GbCpuState *cpu)
{
    const uint8_t lsb = gb_mmu_read(cpu->mmu, cpu->regs.PC++);
    const uint8_t msb = gb_mmu_read(cpu->mmu, cpu->regs.PC++);
    const uint16_t data = (uint16_t)((msb << 8) | lsb);
    return data;
}

bool gb_cpu_decode_instruction(GbCpuState *cpu, const uint8_t instruction)
{
    (void) cpu;
    (void) instruction;
    return true;
}
