#include "avm2/avm32.hpp"

int main() {
    AVM::CPU cpu(500);

    std::vector<byte> prog = {
        MOV_MEM_REG, 0x01, 0x00, reg_r1,
        MOV_LIT_REG, 0x00, 0x01, reg_r2,
        ADD, reg_r1, reg_r2,
        MOV_REG_MEM, reg_acc, 0x01, 0x00,
        JNE, 0xFF, 0xFF, 0x00, 0x00,
        STOP
    };

    cpu.loadprogram(prog);
    cpu.run();

    return 0;
}
