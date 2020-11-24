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
    int inst, reg1, reg2, reg0, reg, address, eq, lt, gt, cond;
    int pc = registers[PC];
    system_bus(pc, &inst, READ);
    int opcode = inst >> 24;
    //for info below, comment out if not needed
    decoded *d = decode(inst);
    printf("%s===s\n",disassemble(d));
    printf("PC: 0x%08x, inst: 0x%x, ", pc, inst);
    switch (opcode) { 
        case LDR:
            printf("ldr\n");
            reg = inst >> 16 & 0xff;
            address = inst & 0xffff;
            if (address > 1023 || reg > 15) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[reg] = memory_fetch_word(address);
            pc += 4;
            break;
        case STR:
            printf("str\n");
            reg = inst >> 16 & 0xff;
            address = inst & 0xffff;
            if (address > 1023 || reg > 15) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[reg] = address;
            pc += 4;
            break;
        case LDX:
            printf("ldx\n");
            reg0 = inst & 0xff;
            address = inst >> 16 & 0xff;
            reg1 = inst >> 8 & 0xff;
            if (address > 1023 || (reg0 > 15 || reg1 > 15)) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = memory_fetch_word(registers[reg0] + reg1);
            pc += 4;
            break;
        case STX:
            printf("stx\n");
            pc += 4;
            break;
        case MOV:
            reg = inst & 0xff;
            address = inst << 16 & 0xff;
            if (address > 1023 || reg > 15) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg];
            pc += 4;
            cpsr = get_cpsr();
            //this print statement is almost right. Good enough for 
            //now- need to fix for this and the rest before completion though
            printf("mov r%x, r%x\nCPSR: 0x%x\n", registers[reg], reg, cpsr);
            break;
        case ADD:
            printf("add\n");
            reg1 = inst >> 8 & 0xff;
            reg2 = inst & 0xff;
            reg = inst >> 16 & 0xff;
            if (reg1 > 15 || reg2 > 15 || reg > 15) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[reg] = registers[reg1] + registers[reg2];
            pc += 4;
            break;
        case SUB:
            printf("sub\n");
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = inst >> 16 & 0xff;
            if (address > 1023 || (reg0 > 15 || reg1 > 15)) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] - registers[reg1];
            pc += 4;
            break;
        case MUL:
            printf("mul\n");
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = inst >> 16 & 0xff;
            if (address > 1023 || (reg0 > 15 || reg1 > 15)) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] * registers[reg1];
            pc += 4;
            break;
        case DIV:
            printf("div\n");
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = inst >> 16 & 0xff;
            if (address > 1023 || (reg0 > 15 || reg1 > 15)) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg1] / registers[reg0];
            pc += 4;
            break;
        case AND:
            printf("and\n");
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = inst >> 16 & 0xff;
            if (address > 1023 || (reg0 > 15 || reg1 > 15)) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] & registers[reg1];
            pc += 4;
            break;
        case ORR:
            printf("orr\n");
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = inst >> 16 & 0xff;
            if (address > 1023 || (reg0 > 15 || reg1 > 15)) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] | registers[reg1];
            pc += 4;
            break;
        case EOR:
            printf("eor\n");
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = inst >> 16 & 0xff;
            if (address > 1023 || (reg0 > 15 || reg1 > 15)) {
                printf("Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] ^ registers[reg1];
            pc += 4;
            break;
        case CMP:
            printf("cmp\n");
            reg1 = inst >> 8 & 0xff;
            reg2 = inst & 0xff;
            if (reg1 > 15 || reg2 > 15) {
                printf("Register out of bounds.\n");
                exit(-1);
            }
            eq = registers[reg1] == registers[reg2];
            lt = registers[reg1] < registers[reg2];
            gt = registers[reg1] > registers[reg2];
            if (eq) {
                bit_set(&cpsr, eq);
                bit_clear(&cpsr, lt);
                bit_clear(&cpsr, gt);
            } else if (lt) {
                bit_set(&cpsr, lt);
                bit_clear(&cpsr, eq);
                bit_clear(&cpsr, gt);
            } else if (gt) {
                bit_set(&cpsr, gt);
                bit_clear(&cpsr, lt);
                bit_clear(&cpsr, eq);
            }
            pc += 4;
            break;
        case B:
            cond = inst >> 16;
            cond = cond << 23;
            printf("%x\n", cond);
            /** if(cond == BAL) {

            }

            address = inst & 0xffff;
            if (address > 1023) {
                printf("Address out of bounds.\n");
                exit(-1);
            }
            pc = address;*/
            break;
        default:
            printf("Invalid instruction recieved.");
            exit(-1);
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
    
    // Save state of original registers / memory.
    int original_reg[15];
    for (int i = 0; i < 15; i++) { 
        original_reg[i] = registers[i]; 
    }

    int original_mem[32][2];
    int addr = 0x100;
    for (int i = 0; i < 32; i++) {
        int temp;
        system_bus(addr, &temp, READ);
        original_mem[i][1] = addr;
        original_mem[i][2] = temp;
        addr += 4;
    }

    step();

    // Check if there is a change, if so, print change.
    for (int i = 0; i < 15; i++) {
        if (original_reg[i] != registers[i]) {
            printf("R[%d]:\t0x%.8X\n\t0x%.8X\n\n", i, original_reg[i], registers[i]);
        }
    }
    int temp;
    addr = 0x100;
    for (int i = 0; i < 32; i++) {
        system_bus(addr, &temp, READ);
        if (original_mem[i][2] != temp) {
            printf("0x%.3X:\t0x%.8X\n\t0x%.8X\n\n", addr, original_mem[i][2], temp);
        }
        addr += 4;
    }
}

