#ifndef clox_chunk_hpp
#define clox_chunk_hpp

#include "common.hpp"
#include "value.hpp"

enum OpCode {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
};

//chunk -> a block of bytecode
class Chunk {
    std::vector<uint8_t> code;
    std::vector<std::pair<int, int> > lines;
    std::vector<Value>   constants;
public:
    Chunk();

    int         add_constant(Value value);
    int         read_line(int offset);
    Value       read_constant(int offset);
    uint8_t*    read_instruction(int offset);
    int         size();
    void        write(uint8_t byte, int line);
};

#endif
