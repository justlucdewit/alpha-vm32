#include "avm2/avm32.hpp"
#include <cmath>

class ScreenDevice : public AVM::Device{
public:
    void call(mem address, mem value) override{
        std::cout << (char) value;
    };
};



int main() {
    AVM::MemoryMapper MM;
    ScreenDevice screen;
    MM.map(&screen, 0x0300, 0x0300, true);
    AVM::CPU cpu(MM, 60000);

    std::vector<byte> prog = {
        MOV_LIT_MEM, 0x00, 0x48, 0x03, 0x00,
        STOP,
    };

    cpu.loadProgram(prog);
    cpu.run();

    return 0;
}
