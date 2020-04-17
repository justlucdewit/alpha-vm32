#include "avm2/avm32.hpp"
#include <cmath>

class ScreenDevice : public AVM::Device{
public:
    void call(mem address, mem value) override{
        std::cout << value << "\n";
    };
};

int main() {
    AVM::MemoryMapper MM;
    ScreenDevice screen;
    MM.map(&screen, 0x0300, 0x0302, true);
    AVM::CPU cpu(MM, 60000);

    std::vector<byte> prog = {
        INC_REG, reg_acc,
        MOV_REG_MEM, reg_acc, 0x03, 0x01,
        JGT_LIT, 0xFF, 0xFF, 0x00, 0x00,
        STOP,
    };
    cpu.loadProgram(prog);
    cpu.run();

    return 0;
}
