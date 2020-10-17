CC=g++
CPPFLAGS= -std=c++17 -I
DEPS = chunk.hpp common.hpp debug.hpp value.hpp vm.hpp
OBJ  = main.o chunk.o debug.o value.o vm.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

klox: $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f klox $(OBJ)
