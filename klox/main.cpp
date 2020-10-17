#include "common.hpp"
#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"

int main(int argc, const char* argv[]) {
	Chunk chunk;
	VM vm;
	int constant = chunk.add_constant(1.2);
	chunk.write(OP_CONSTANT, 123);
	chunk.write(constant, 123);

	constant = chunk.add_constant(3.4);
	chunk.write(OP_CONSTANT, 123);
	chunk.write(constant, 123);

	chunk.write(OP_ADD, 123);

	constant = chunk.add_constant(5.6);
	chunk.write(OP_CONSTANT, 123);
	chunk.write(constant, 123);

	chunk.write(OP_DIVIDE, 123);

	chunk.write(OP_NEGATE, 123);
	chunk.write(OP_RETURN, 123);
	vm.interpret(&chunk);
	return 0;
}
