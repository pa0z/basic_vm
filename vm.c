#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX]; // 65536 locations stored memory in array

// registers
enum{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

uint16_t[R_COUNT] // stored registers in array

// instruction set
enum{
    OP_BR = 0, // branch
    OP_ADD, // add (obviosly)
    OP_LD, // load
    OP_ST, // store
    OP_JSR, // jump register
    OP_AND, // bitwise and
    OP_LDR, // load register
    OP_STR, // store register
    OP_RTI, // unused
    OP_NOT, // bitwise not
    OP_LDI, // load indirect
    OP_STI, // store indirect
    OP_JMP, // jump
    OP_RES, // reserved (unused)
    OP_LEA, // load effective address
    OP_TRAP, // execute trap
};

// cond flags
enum{
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2
};

int main(int argc, const char* argv[]){
    // loading args
    if (argc < 2){
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; j++){
        if (!read_image(argv[j])){
            printf("failed to load image: %\n", argv[j]);
            exit(1);
        }
    }

    // initial setup
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();


// cond intitialised to 0
reg[R_COND] = FL_ZRO;

// set PC to starting position, default 0x3000
enum {PC_START = 0x3000};
reg[R_PC] = PC_START;

int running = 1;
while (running){
    // fetch
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op = instr >> 12;

    switch (op) {
        case OP_ADD:
            @{ADD}
            break;
        case OP_AND:
            @{AND}
            break;
        case OP_NOT:
            @{NOT}
            break;
        case OP_BR:
            @{BR}
            break;
        case OP_JMP:
            @{JMP}
            break;
        case OP_JSR:
            @{JSR}
            break;
        case OP_LD:
            @{LD}
            break;
        case OP_LDI:
            @{LDI}
            break;
        case OP_LDR:
            @{LDR}
            break;
        case OP_LEA:
            @{LEA}
            break;
        case OP_ST:
            @{ST}
            break;
        case OP_STI:
            @{STI}
            break;
        case OP_STR:
            @{STR}
            break;
        case OP_TRAP:
            @{TRAP}
            break;
        case OP_RES:
        case OP_RTI:
        default:
            @{BAD OPCODE}
            break;
    }
}
}
