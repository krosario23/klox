#ifndef clox_debug_hpp
#define clox_debug_hpp

#include "chunk.hpp"

void disassemble_chunk(Chunk* chunk, const char* name);
int disassemble_instruction(Chunk* chunk, int offset);

#endif
