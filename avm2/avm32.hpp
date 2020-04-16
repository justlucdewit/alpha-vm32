#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
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
#define reg_sp 0x0A
#define reg_fp 0x0B

// instructions
#define NOP 0x00
#define MOV_LIT_REG 0x01
#define MOV_REG_REG 0x02
#define MOV_REG_MEM 0x03
#define MOV_MEM_REG 0x04

#define PUSH_LIT 0x17
#define PUSH_REG 0x18
#define POP 0x1A

#define CAL_LIT 0x5E
#define CAL_REG 0x5F
#define RET 0x70

#define ADD 0x10
#define SUB 0x11
#define MUL 0x12
#define DIV 0x13

#define JNE 0x20

#define STOP 0xFF

typedef uint16_t mem;
typedef uint8_t byte;

namespace AVM{
    class Device{
    public:
        virtual void call(mem, mem){std::cout << "base class";};
    };

    struct MemoryRegion{
    public:
        Device* device;
        uint16_t start;
        uint16_t end;
        bool remap;
        bool exist = true;
    };

    class MemoryMapper{
    public:
        std::vector<MemoryRegion> regions;

        void map(Device* device, uint16_t start, uint16_t end, bool remap){
            MemoryRegion newRegion;
            newRegion.device = device;
            newRegion.start = start;
            newRegion.end = end;
            newRegion.remap = remap;
            regions.push_back(newRegion);
        }

        MemoryRegion findRegion(uint16_t address){
            for (const auto region : regions){
                if (region.start <= address && region.end >= address){
                    return region;
                }
            }

            MemoryRegion nonExist;
            nonExist.exist = false;
            return nonExist;
        }

        char checkDevice(mem address, mem value){
            MemoryRegion region = findRegion(address);
            if (region.exist){
                region.device->call(address, value);
            }
            return 0;
        }
    };

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
        mem sp = 0;  // stack pointer
        mem fp = 0; // frame pointer
        byte stop = 0; // internal stop register

        mem stackFrameSize = 0; // internal register
        MemoryMapper memMap;

        // fde cycle
        mem* getRegister(byte);
        byte fetchSingle();
        mem fetchDouble();
        void execute(byte);

        // helpers
        void pushToStackDouble(mem);
        void pushToStackSepperate(byte, byte);
        mem pop();

        void pushState();
        void popState();
        void setMemory(mem, mem);

    public:
        std::vector<byte> memory;
        explicit CPU(MemoryMapper, int);
        void debug();
        void loadprogram(std::vector<byte>&);
        void run();
        void runDebug();
    };
}