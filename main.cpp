#include "avm2/avm32.hpp"

int main() {
    AVM::CPU cpu(500);

    std::vector<byte> prog = {
            0x01, 0x12, 0x34, 0x01, // mov 0x1234, r1
            0x01, 0xAB, 0xCD, 0x02, // mov 0xABCD, r2
            0x10, 0x01, 0x02,       // add r1, r2
            0x03, 0x00, 0x01, 0x00, // mov acc, 0x0100
            0xFF                    // stop
    };

    cpu.loadprogram(prog);
    cpu.run();

    return 0;
}
