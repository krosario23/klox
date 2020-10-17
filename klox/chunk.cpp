#include <iostream>

#include "chunk.hpp"

Chunk::Chunk() {
    //do nothing
}

int Chunk::add_constant(Value value) {
    constants.push_back(value);
    return constants.size() - 1;
}

//returns line number of instruction at given offset
int Chunk::read_line(int offset) {
    int line = 0;
    for (std::pair<int, int> p : lines) {
        if (offset >= p.second) {
            offset -= p.second;
        } else {
            line = p.first;
            break;
        }
    }
    //std::cout << "line: " << line;
    return line;
}

//returns constant at given offset
Value Chunk::read_constant(int offset) {
    return constants[offset];
}

//returns instruction at given offset
uint8_t* Chunk::read_instruction(int offset) {
    return &code[offset];
}

//returns the length of the code vector
int Chunk::size() {
    return code.size();
}

//adds the given byte to the current chunk
void Chunk::write(uint8_t byte, int line) {
    code.push_back(byte);
    if (!lines.empty() && lines.back().first == line) {
        //std::cout << "repeat line" << std::endl;
        lines.back().second++;
    } else {
        //std::cout << "new line" << std::endl;
        lines.push_back(std::make_pair(line, 1));
    }
}
