#include "avm32.hpp"

AVM::CPU::CPU(mem size){
    memory.resize(size);
    sp = size-2;
    fp = size-2;
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

        case PUSH_LIT: {
            memory[sp] = fetchSingle();
            memory[sp-1] = fetchSingle();
            sp-=2;
            return;
        }

        case PUSH_REG: {
            mem val = *getRegister(fetchSingle());
            memory[sp] = val >> 8;
            memory[sp-1] = val;
            sp-=2;
            return;
        }

        case POP: {
            sp+=2;
            *getRegister(fetchSingle()) = memory[sp]*256 + memory[sp-1];
            return;
        }

        case CAL_LIT: {
            mem adress = fetchDouble();


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
        case 0x0A: return &sp;
        case 0x0B: return &fp;
        default: return nullptr;
    }
}

void AVM::CPU::debug(){
    std::cout << "ip  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << ip << std::endl;
    std::cout << "acc = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right  << std::hex << acc << std::endl;
    std::cout << "sp  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << sp << std::endl;
    std::cout << "fp  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << fp << std::endl;
    std::cout << "r1  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r1 << std::endl;
    std::cout << "r2  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r2 << std::endl;
    std::cout << "r3  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r3 << std::endl;
    std::cout << "r4  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r4 << std::endl;
    std::cout << "r5  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r5 << std::endl;
    std::cout << "r6  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r6 << std::endl;
    std::cout << "r7  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r7 << std::endl;
    std::cout << "r8  = 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << r8 << "\n" << std::endl;
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

void AVM::CPU::pushToStack(mem val) {
    
}



