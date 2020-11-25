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
    int inst, reg1, reg2, reg0, reg, address, eq, lt, gt, move, rn_loc, total;
    int pc = registers[PC];
    
    system_bus(pc, &inst, READ);

    decoded *decoded = decode(inst);
    int opcode = decoded->opcode;

    //for info below, comment out if not needed
    printf("PC: 0x%.8x, inst: 0x%.8x, %s\n", pc, inst, disassemble(decoded));
    switch (opcode) { 
        case LDR:
            reg = inst >> 16 & 0xff;
            address = decoded->address;
            if (address > 1023 || reg > 16) {
                printf("LDR Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[reg] = memory_fetch_word(address);
            pc += 4;
            break;
        case STR:
            reg = inst >> 16 & 0xff;
            address = decoded->address;
            if (address > 1023 || reg > 16) {
                printf("STR Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[reg] = address;
            pc += 4;
            break;
        case LDX:
            reg0 = inst & 0xff;
            address = decoded->address;
            reg1 = inst >> 8 & 0xff;
            if (address > 1023 || (reg0 > 16 || reg1 > 16)) {
                printf("LDX Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = memory_fetch_word(registers[reg0] + reg1);
            pc += 4;
            break;
        case STX:
            reg0 = inst &0xff;
            address = inst >> 16 & 0xff;
            reg1 = inst >> 8 & 0xff;
            registers[address] = memory_fetch_word(registers[reg0] + reg1);
            pc += 4;
            set_reg(PC, pc);
            break;
        case MOV:
            if (decoded->address > 1023 || (decoded->rn > 16 || decoded->rm > 16)) {
                printf("MOV Address/Register out of bounds.\n");
                exit(-1);
            }
            rn_loc = get_reg(decoded->rn);
            if (decoded->condition == 128) {
                move = rn_loc;
            } else {
                move = decoded->immediate;
            }
            set_reg(decoded->rd, move);
            pc += 4;
            set_reg(15, pc);
            break;
        case ADD:
            total = registers[decoded->rn] + registers[decoded->rm];
            pc += 4;
            set_reg(decoded->rd, total);
            break;
        case SUB:
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = decoded->address;
            if (address > 1023 || (reg0 > 16 || reg1 > 16)) {
                printf("SUB Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] - registers[reg1];
            pc += 4;
            break;
        case MUL:
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = decoded->address;
            if (address > 1023 || (reg0 > 16 || reg1 > 16)) {
                printf("MUL Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] * registers[reg1];
            pc += 4;
            break;
        case DIV:
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = inst >> 16 & 0xff;
            if (address > 1023 || (reg0 > 16 || reg1 > 16)) {
                printf("DIV Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg1] / registers[reg0];
            pc += 4;
            break;
        case AND:
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = decoded->address;
            if (address > 1023 || (reg0 > 16 || reg1 > 16)) {
                printf("AND Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] & registers[reg1];
            pc += 4;
            break;
        case ORR:
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = decoded->address;
            if (address > 1023 || (reg0 > 16 || reg1 > 16)) {
                printf("ORR Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] | registers[reg1];
            pc += 4;
            break;
        case EOR:
            reg0 = inst >> 8 & 0xff;
            reg1 = inst & 0xff;
            address = decoded->address;
            if (address > 1023 || (reg0 > 16 || reg1 > 16)) {
                printf("EOR Address/Register out of bounds.\n");
                exit(-1);
            }
            registers[address] = registers[reg0] ^ registers[reg1];
            pc += 4;
            break;
        case CMP:
            reg1 = decoded->rm;
            reg2 = decoded->rn;
            if (reg1 > 16 || reg2 > 16) {
                printf("CMP Register out of bounds.\n");
                exit(-1);
            }
            if (decoded->address > 1023) {
                printf("CMP Address out of bounds.\n");
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
            if (decoded->condition == BAL) {
                registers[PC] = decoded->address;
                pc += 4;
                set_reg(PC, pc);
            } else if (decoded->condition == BEQ) {
                system_bus(pc, &inst, READ);
                if (registers[Z]== 1) {
                    registers[PC] = decoded->address;
                    pc += 4;
                    set_reg(PC, pc);
                } else {
                    cpsr = 0;
                    pc += 4;
                    set_reg(PC, pc);
                }
            } else if (decoded->condition == BNE) {
                system_bus(decoded->address, &inst, READ);
                if (registers[Z] == 0) {
                    registers[PC] = decoded->address;
                    pc += 4;
                    set_reg(PC, pc);
                } else {
                    cpsr = 0;
                    pc += 4;
                    set_reg(PC, pc);
                }
            } else if (decoded->condition == BLE) {
                if (registers[Z] == 1 || registers[N] != registers[V]) {
                    registers[PC] = decoded->address;
                    pc += 4;
                    set_reg(PC, pc);
                } else {
                    cpsr = 0;
                    pc += 4;
                    set_reg(PC, pc);
                }
            } else if (decoded->condition == BLT) {
                if (registers[N] != registers[V]) {
                    registers[PC] = decoded->address;
                    pc += 4;
                    set_reg(PC, pc);
                } else {
                    cpsr = 0;
                    pc += 4;
                    set_reg(PC, pc);
                }
            } else if (decoded->condition == BGE) {
                if (registers[N] == registers[V]) {
                    registers[PC] = decoded->address;
                    pc += 4;
                    set_reg(PC, pc);
                } else {
                    cpsr = 0;
                    pc += 4;
                    set_reg(PC, pc);
                }
            } else if (decoded->condition == BGT) {
                if (registers[Z] == 0 && registers[N] == registers[V]) {
                    registers[PC] = decoded->address;
                    pc += 4;
                    set_reg(PC, pc);
                } else {
                    cpsr = 0;
                    pc += 4;
                    set_reg(PC, pc);
                }

            } else if (decoded->condition == BL) {
                pc += 4;
                set_reg(R14, pc);
                registers[PC] = decoded->address;
            } else {
                printf("Invalid instrunction.\n");
                exit(-1);
            }

            break;
        default:
            printf("Invalid instruction recieved.\n");
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
    int original_reg[15];
    for (int i = 0; i < 15; i++) { original_reg[i] = registers[i]; }
    step();
    for (int i = 0; i < 15; i++) {
        if (original_reg[i] != registers[i]) {
            printf("R[%d]:\t0x%.8X\n\t0x%.8X\n\n", i, original_reg[i], registers[i]);
        }
    };
}

void step_show_reg_mem() {
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

