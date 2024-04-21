CC=g++
CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal\
       -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
       -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions\
	   -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security\
	   -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor\
	   -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
	   -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla\
	   -D_DEBUG -mavx2 -mfma -mavx -msse4.2 -DNDEBUG -DLINEAR_BUILD

all: test.o binary_heap.o
	$(CC) $(CFLAGS) test.o binary_heap.o -o binary_heap.out

test.o : test.cpp
	$(CC) $(CFLAGS) -c test.cpp -o test.o

binary_heap.o : binary_heap.cpp
	$(CC) $(CFLAGS) -c binary_heap.cpp -o binary_heap.o

clean:
	rm test.o binary_heap.o