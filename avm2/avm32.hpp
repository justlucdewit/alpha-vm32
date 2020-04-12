#pragma once
#include <vector>
#include <iostream>
#include <string>

// registers
#define reg_acc 0x00
#define reg_r1 0x01
#define reg_r2 0x02
#define reg_r3 0x03
#define reg_r4 0x04
#define reg_r5 0x05
#define reg_r6 0x06
#define reg_r7 0x07
#define reg_r8 0x08
#define reg_ip 0x09

// instructions
#define NOP 0x00
#define MOV_LIT_REG 0x01
#define MOV_REG_REG 0x02
#define MOV_REG_MEM 0x03
#define MOV_MEM_REG 0x04

#define ADD 0x10
#define SUB 0x11
#define MUL 0x12
#define DIV 0x13

#define JNE 0x20

#define STOP 0xFF

typedef uint16_t mem;
typedef uint8_t byte;

namespace AVM{
    class CPU{
        mem r1 = 0; // general purpose register
        mem r2 = 0; // general purpose register
        mem r3 = 0; // general purpose register
        mem r4 = 0; // general purpose register
        mem r5 = 0; // general purpose register
        mem r6 = 0; // general purpose register
        mem r7 = 0; // general purpose register
        mem r8 = 0; // general purpose register
        mem ip = -1; // instruction pointer
        mem acc = 0; // accumulator
        byte stop = 0;


        //fde cycle
        mem* getRegister(byte);
        byte fetchSingle();
        mem fetchDouble();
        void execute(byte);

    public:
        std::vector<byte> memory;
        explicit CPU(mem);
        void debug();
        void loadprogram(std::vector<byte>&);
        void run();
        void runDebug();
    };
}