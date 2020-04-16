#include "avm2/avm32.hpp"

class ScreenDevice : public AVM::Device{
public:
    void call(mem, mem) override{
        std::cout << "screenDevice has been called!";
    };
};

int main() {
    AVM::MemoryMapper MM;
    ScreenDevice screen;
    MM.map(&screen, 0x0300, 0x03FF, true);
    AVM::CPU cpu(MM, 60000);

    std::vector<byte> prog = {
        MOV_LIT_REG, 0x03, 0x66, reg_r1,
        MOV_REG_MEM, reg_r1, 0x03, 0x66,
        STOP,
    };

    cpu.loadprogram(prog);
    cpu.run();

    return 0;
}
