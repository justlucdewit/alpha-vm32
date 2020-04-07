#include "avm32.hpp"

/*
 * Instuctions:
 * header: 2 bits
 * data: 30 bits
 *
 * header:
 * 00 => positive integer
 * 01 => primative instruction
 * 10 => negative integer
 * 11 => undefined
 */

AVM32::AVM32(unsigned int programSize, unsigned int stackSize){
    memory.resize(programSize + stackSize);
    pc = stackSize;
}

int32_t AVM32::getType(int32_t instruction) {
    int32_t type = 0xc0000000;
    type = (type & instruction) >> 30;
    return std::abs(type);
}

int32_t AVM32::getData(int32_t instruction) {
    int32_t data = 0x3fffffff;
    data = (data & instruction);
    return data;
}

void AVM32::fetch() {
    pc++;
}

void AVM32::decode() {
    typ = getType(memory[pc]);
    dat = getData(memory[pc]);
}

void AVM32::execute() {
    //std::cout << "data = " << dat << " ";
    //std::cout << "type = " << typ << "\n";

    switch(typ){
        case 0: {
            sp++;
            //std::cout << "push " << dat << "\n";
            memory[sp] = dat;
            break;
        }
        case 1: {
            doPrimitive();
            break;
        }
        case 2: {
            sp++;
            //std::cout << "push " << -dat << "\n";
            memory[sp] = -dat;
            break;
        }
    }
}

void AVM32::doPrimitive() {
    switch (dat){
        case 0:// halt
            //std::cout << "halt " << memory[sp] << "\n";
            running = 0;
            break;

        case 1:// add
            //std::cout << "add " << memory[sp-1] << " " << memory[sp] << "\n";
            memory[sp-1] = memory[sp-1] + memory[sp];
            sp--;
            break;

        case 2:// sub
            //std::cout << "sub " << memory[sp-1] << " " << memory[sp] << "\n";
            memory[sp-1] = memory[sp-1] - memory[sp];
            sp--;
            break;

        case 3:// mul
            //std::cout << "mul " << memory[sp-1] << " " << memory[sp] << "\n";
            memory[sp-1] = memory[sp-1] * memory[sp];
            sp--;
            break;

        case 4:// div
            //std::cout << "div " << memory[sp-1] << " " << memory[sp] << "\n";
            memory[sp-1] = memory[sp-1] / memory[sp];
            sp--;
            break;

        case 5:// mod
            //std::cout << "mod " << memory[sp-1] << " " << memory[sp] << "\n";
            memory[sp-1] = memory[sp-1] % memory[sp];
            sp--;
            break;

        case 6:// prtn
            //std::cout << "prtn " << memory[sp] << "\n";
            std::cout << memory[sp];
            break;

        case 7:// prtc
            //std::cout << "prtc " << memory[sp] << "\n";
            std::cout <<  (char) memory[sp];
            break;
    }
}

void AVM32::run() {
    pc -= 1;
    while(running == 1){
        fetch();
        decode();
        execute();
        //showStack();
    }
}

void AVM32::showStack() {
    int i = 0;
    std::cout << "stack: [";
    while(i++ != sp+1) {
        if (i == 1)
            std::cout << memory[i - 1];
        else
            std::cout << ", " << memory[i - 1];
    }
    std::cout << "]\n\n";
}

void AVM32::loadProgram(std::vector<int32_t> prog) {
    for (int32_t i = 0; i < prog.size(); i++){
        memory[pc + i] = prog[i];
    }
}