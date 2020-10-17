#include "debug.hpp"
#include "value.hpp"

#include <stdio.h>
#include <iostream>

static int constant_instruction(const char* name, Chunk* chunk,
                               int offset) {
    uint8_t constant = *chunk->read_instruction(offset + 1);
    //print the instruction name (width = 16), pad with spaces
    //print the constant index (width = 4)
    printf("%-16s %4d '", name, constant);
    //print the constant value
    print_value(chunk->read_constant(constant));
    printf("'\n");
    return offset + 2;
}

static int simple_instruction(std::string name, int offset) {
    std::cout << name << std::endl;    //print the name of the instruction
    return offset + 1;
}

int disassemble_instruction(Chunk* chunk, int offset) {
    //some formatting
    printf("%04d ", offset);

    if (offset > 0 && chunk->read_line(offset) == chunk->read_line(offset - 1)) {
        std::cout << "   | ";
    } else {
        printf("%4d ", chunk->read_line(offset));
    }

    //get the instruction at the given offset in our bytecode vector
    uint8_t instruction = *chunk->read_instruction(offset);

    //switch on the instruction to print correct disassembly
    switch (instruction) {
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);
        case OP_ADD:
            return simple_instruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simple_instruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simple_instruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simple_instruction("OP_DIVIDE", offset);
        case OP_NEGATE:
            return simple_instruction("OP_NEGATE", offset);
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        default:
            std::cout << "unknown opcode " << instruction << std::endl;
            return offset + 1;
    }
}

void disassemble_chunk(Chunk* chunk, const char* name) {
    //print a header
    std::cout << "== " << name << " ==" << std::endl;

    //loop through the whole bytecode vector and disassemble each instruction
    for (int offset = 0; offset < chunk->size();) {
        offset = disassemble_instruction(chunk, offset);
    }
}
