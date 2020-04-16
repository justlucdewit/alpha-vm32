#include "avm2/avm32.hpp"
#include <cmath>

class ScreenDevice : public AVM::Device{
public:
    void call(mem address, mem value) override{
        std::cout << (char) value;
    };
};

class ScreenMatrixDevice : public AVM::Device{
public:
    void call(mem address, mem value) override{
        const mem x = (address % 16) + 1;
        const mem y = std::floor(address/16)+1;
        std::cout << "\033[" << y << ";" << x << "H";
        std::cout << (char) value;
    };
};

int main() {
    AVM::MemoryMapper MM;
    ScreenMatrixDevice screen;
    MM.map(&screen, 0x0300, 0x03FF, true);
    AVM::CPU cpu(MM, 60000);

    std::vector<byte> prog = {
        MOV_LIT_MEM, 0x00, 0x48, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x65, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x6C, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x6C, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x6F, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x20, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x57, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x6F, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x72, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x6C, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x64, 0x03, 0x00,
        MOV_LIT_MEM, 0x00, 0x21, 0x03, 0x00,
        STOP,
    };

    cpu.loadprogram(prog);
    cpu.run();

    return 0;
}
