#pragma once
#include <vector>

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
        mem ip = 0; // instruction pointer
        mem acc = 0; // accumulator
        std::vector<byte> memory;

        //fde cycle
        byte fetchSingle();
        mem fetchDouble();
        mem decode();
        void execute(byte);
        void step();

    public:
        explicit CPU(mem);
    };
}