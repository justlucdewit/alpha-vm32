#include "avm2/avm32.hpp"

int main() {
    AVM::CPU cpu(500);

    std::vector<byte> prog = {
        MOV_LIT_REG, 0x12, 0x34, reg_r1,
        MOV_LIT_REG, 0xAB, 0xCD, reg_r2,
        PUSH_REG, reg_r1,
        PUSH_REG, reg_r2,
        POP, reg_r1,
        POP, reg_r2,
        STOP
    };

    cpu.loadprogram(prog);
    cpu.runDebug();

    return 0;
}
