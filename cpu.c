#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "memory_system.h"
#include "bit_functions.h"
#include "cpu.h"
#include "isa.h"

static int registers[16];

static int cpsr; // status register

/* For future implementation of breakpoints
 *
#define NUM_BREAKPOINTS 2
static int breakpoints[NUM_BREAKPOINTS]; // allow 2 break points
 */

void set_reg(int reg, int value) {
    registers[reg] =  value;
}

int get_reg(int reg) {
    return registers[reg];
}

int get_cpsr() {
    return cpsr;
}

void show_regs() {
    printf("reg0: 0x%08x, reg1: 0x%08x, reg2: 0x%08x, reg3: 0x%08x\n", registers[0], registers[1], registers[2], registers[3]);
    printf("reg4: 0x%08x, reg5: 0x%08x, reg6: 0x%08x, reg7: 0x%08x\n", registers[4], registers[5], registers[6], registers[7]);
    printf("reg8: 0x%08x, reg9: 0x%08x, reg10: 0x%08x, reg11: 0x%08x\n", registers[8], registers[9], registers[10], registers[11]);
    printf("reg12: 0x%08x, reg13: 0x%08x, reg14: 0x%08x, reg15: 0x%08x\n", registers[12], registers[13], registers[14], registers[15]);
}

//fetch decode execute
void step() {
    int inst, reg1, reg2, reg3, reg0, reg, address, immediate, eq, lt, gt;
    int pc = registers[PC];
    system_bus(pc, &inst, READ);
    int opcode = inst >> 24;
    printf("PC: %x, Opcode: %x, Instruction: %x\n", pc, opcode, inst);
    switch (opcode) { 
    case LDR:
        printf("LDR reached\n");
        pc += 4;
        break;
    case STR:
        printf("STR reached\n");
        pc += 4;
        break;
    case LDX:
        printf("LDX reached\n");
        pc += 4;
        break;
    case STX:
        printf("LDX reached\n");
        pc += 4;
        break;
    case MOV:
        printf("MOV reached\n");
        pc += 4;
        break;
    case ADD:
        printf("ADD reached\n");
        pc += 4;
        break;
    case SUB:
        printf("SUB reached\n");
        pc += 4;
        break;
    case MUL:
        printf("MUL reached\n");
        pc += 4;
        break;
    case DIV:
        printf("DIV reached\n");
        pc += 4;
        break;
    case AND:
        printf("AND reached\n");
        pc += 4;
        break;
    case ORR:
        printf("ORR reached\n");
        pc += 4;
        break;
    case EOR:
        printf("EOR reached\n");
        pc += 4;
        break;
    case CMP:
        printf("CMP reached\n");
        pc += 4;
        break;
    case B:
        printf("B reached\n");
        //pc = address;
        break;    
    }
    registers[15] = pc; 
}

void step_n(int n) {
    for (int i = 0; i < n; i++) {
        step();
    }
}

void step_show_reg() {
    step();
    show_regs();
}

void step_show_reg_mem() {
    step_show_reg();
    //some other method call to show memory

    /*f. step_show_reg​ shall display ​step​’s display plus it shall display the values ofregisters changed by the instruction.
    PC: 0x00000128, inst: 0x31000003, add r0, r0, r3CPSR: 0x40000000reg[0]: before: 0x00000064, after: 0x00000067reg[15]: before: 0x00000128, 
    after: 0x0000012cg.step_show_reg_mem​ shall display ​step_show_reg​’s display plus it shall displaythe values of memory locations changed by 
    the instruction.PC: 0x0000012c, inst: 0x12000104, str r0, 0x104CPSR: 0x40000000reg[15]: before: 0x0000012c, after: 0x00000130addr: 0x0104, 
    before: 0x00000010, after: 0x00000067*/
}

