#include "avm2/avm32.hpp"

int main() {
    AVM::CPU cpu(500);

    cpu.memory[0] = 0x01;
    cpu.memory[1] = 0x12;
    cpu.memory[2] = 0x34;
    return 0;
}
