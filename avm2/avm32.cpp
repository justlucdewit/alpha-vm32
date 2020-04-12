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
        // mov lit->reg
        case MOV_LIT_REG: {
            mem lit = fetchDouble();
            *getRegister(fetchSingle()) = lit;
            return;
        }

        case MOV_REG_REG: {
            mem from = *getRegister(fetchSingle());
            *getRegister(fetchSingle()) = from;
            return;
        }

        case MOV_REG_MEM: {//movrm too from
            mem reg = *getRegister(fetchSingle());
            mem address = fetchDouble();
            memory[address] = reg;
            return;
        }

        case MOV_MEM_REG: {//movmr too from
            mem address = fetchDouble();
            *getRegister(fetchSingle()) = memory[address];
            return;
        }

        //add r1 and r2
        case ADD: {
            mem reg1 = *getRegister(fetchSingle());
            mem reg2 = *getRegister(fetchSingle());
            acc = reg1+reg2;
            return;
        }

        case STOP: {
            stop = 1;
            return;
        }

        case JNE: {

            mem value = fetchDouble();
            //std::cout << "\n!!going to " << value << " !!\n";
            if (value != acc){
                mem adress = fetchDouble();

                ip = adress-1;
            }

            return;
        }

        default: {
            std::cout << "oh noes!";
        }
    }
}

mem *AVM::CPU::getRegister(byte index) {
    switch (index){
        case 0x00: return &acc;
        case 0x01: return &r1;
        case 0x02: return &r2;
        case 0x03: return &r3;
        case 0x04: return &r4;
        case 0x05: return &r5;
        case 0x06: return &r6;
        case 0x07: return &r7;
        case 0x08: return &r8;
        case 0x09: return &ip;
        default: return nullptr;
    }
}

void AVM::CPU::debug(){
    std::cout << "mem0x100 = " << std::to_string(memory[0x100]) << std::endl;
    std::cout << "ip = " << std::uppercase << std::hex << ip << std::endl;
    std::cout << "acc = " << std::uppercase << std::hex << acc << std::endl;
    std::cout << "r1 = " << std::uppercase << std::hex << r1 << std::endl;
    std::cout << "r2 = " << std::uppercase << std::hex << r2 << std::endl;
    std::cout << "r3 = " << std::uppercase << std::hex << r3 << std::endl;
    std::cout << "r4 = " << std::uppercase << std::hex << r4 << std::endl;
    std::cout << "r5 = " << std::uppercase << std::hex << r5 << std::endl;
    std::cout << "r6 = " << std::uppercase << std::hex << r6 << std::endl;
    std::cout << "r7 = " << std::uppercase << std::hex << r7 << std::endl;
    std::cout << "r8 = " << std::uppercase << std::hex << r8 << "\n" << std::endl;
}

void AVM::CPU::run(){
    while(!stop){
        byte instruction = fetchSingle();
        execute(instruction);
    }
}

void AVM::CPU::runDebug(){
    while(!stop){
        debug();
        byte instruction = fetchSingle();
        execute(instruction);
    }
    debug();
}

void AVM::CPU::loadprogram(std::vector<byte>& program) {
    int i = 0;
    for (const auto& b : program){
        memory[i++] = b;
    }
}



