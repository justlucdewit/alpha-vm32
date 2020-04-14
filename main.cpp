#include "avm2/avm32.hpp"

int main() {
    AVM::CPU cpu(500);

    std::vector<byte> prog = {
        // --main program--
        PUSH_LIT, 0x33, 0x33,
        PUSH_LIT, 0x22, 0x22,
        PUSH_LIT, 0x11, 0x11,

        MOV_LIT_REG, 0x12, 0x34, reg_r1,
        MOV_LIT_REG, 0x56, 0x78, reg_r4,

        PUSH_LIT, 0x00, 0x00,
        CAL_LIT, 0x00, 0x17,
        STOP,

        // --sub routine--
        PUSH_LIT, 0x01, 0x02,
        PUSH_LIT, 0x03, 0x04,
        PUSH_LIT, 0x05, 0x06,

        MOV_LIT_REG, 0x07, 0x08, reg_r1,
        MOV_LIT_REG, 0x09, 0x0A, reg_r8,

        RET
    };

    cpu.loadprogram(prog);
    cpu.runDebug();

    return 0;
}
