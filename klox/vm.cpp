#include <iostream>

#include "common.hpp"
#include "debug.hpp"
#include "vm.hpp"

VM::VM() {
    reset_stack();
}

VM::~VM() {

}

void VM::reset_stack() {
    stack.clear();
}

void VM::push(Value value) {
    stack.push_back(value);
}

Value VM::pop() {
    Value result = stack.back();
    stack.pop_back();
    return result;
}

InterpretResult VM::run() {
#define READ_BYTE() (*chunk->read_instruction(ip++))
#define READ_CONSTANT() (chunk->read_constant(READ_BYTE()))
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false)

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            std::cout << "          ";
            for (std::vector<Value>::iterator it = stack.begin(); it != stack.end(); ++it) {
                std::cout << "[ ";
                print_value(*it);
                std::cout << " ]";
            }
            std::cout << std::endl;
            disassemble_instruction(chunk, ip);
        #endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
            case OP_NEGATE: {
                push(-pop());
                break;
            }
            case OP_RETURN: {
                print_value(pop());
                std::cout << std::endl;
                return INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult VM::interpret(Chunk* chunk) {
    this->chunk = chunk;
    this->ip = 0;
    return run();
}
