#include "avm32.hpp"

AVM::CPU::CPU(mem size){
    memory.resize(size);
}

byte AVM::CPU::fetchSingle(){
    return memory[++ip];
}

mem AVM::CPU::fetchDouble() {
    mem num = memory[ip+1]*256 + memory[ip+2];
    ip+=2;
    return num;
}

void AVM::CPU::execute(byte instruction) {
    switch(instruction){
        // move litteral into r1
        case 0x01: {
            r1 = fetchDouble();
            return;
        }

        // move litteral into r1
        case 0x02: {
            r2 = fetchDouble();
            return;
        }

        // move litteral into r1
        case 0x03: {
            r3 = fetchDouble();
            return;
        }

        case 0x04: {
            r4 = fetchDouble();
            return;
        }

        case 0x05: {
            r5 = fetchDouble();
            return;
        }

        case 0x06: {
            r6 = fetchDouble();
            return;
        }

        case 0x07: {
            r7 = fetchDouble();
            return;
        }

        case 0x08: {
            r8 = fetchDouble();
            return;
        }

        //add r1 and r2
        case 0x20: {
            acc = r1+r2;
            return;
        }
    }
}

mem AVM::CPU::decode() {
    return 0;
}

void AVM::CPU::step() {
    byte instruction = fetchSingle();

}

