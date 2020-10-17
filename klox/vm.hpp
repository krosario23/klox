#ifndef clox_vm_hpp
#define clox_vm_hpp

#include <stack>

#include "chunk.hpp"
#include "value.hpp"

enum InterpretResult {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
};

class VM {
  Chunk* chunk;
  std::vector<Value> stack;
  int ip;
public:
    VM();
    ~VM();

    void  reset_stack();
    void  push(Value value);
    Value pop();

    InterpretResult run();
    InterpretResult interpret(Chunk* chunk);
};

#endif
