CC=g++

CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal\
       -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
       -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions\
	   -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security\
	   -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor\
	   -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
	   -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla\
	   -D_DEBUG

all:	test_generate

test_generate:
	$(CC) $(CFLAGS) -c TestGenerator/create_array.cpp    -o TestGenerator/create_array.o
	$(CC) $(CFLAGS) -c TestGenerator/create_requests.cpp -o TestGenerator/create_requests.o
	$(CC) TestGenerator/create_array.o    -o TestGenerator/create_array.exe
	$(CC) TestGenerator/create_requests.o -o TestGenerator/create_requests.exe
	chmod +x TestGenerator/generator.sh
	./TestGenerator/generator.sh

create_fenwick:
	$(CC) $(CFLAGS) -g -c FenwickTree/fenwick_tree.cpp -o FenwickTree/fenwick_tree.o
	$(CC) $(CFLAGS) -g -c FenwickTree/main.cpp 		-o FenwickTree/main.o
	$(CC) FenwickTree/fenwick_tree.o FenwickTree/main.o -o fenwick_tree.exe

create_seg_tree:
	$(CC) $(CFLAGS) -g -c SegmentTree/segment_tree.cpp -o SegmentTree/segment_tree.o
	$(CC) $(CFLAGS) -g -c SegmentTree/main.cpp 		-o SegmentTree/main.o
	$(CC) SegmentTree/segment_tree.o SegmentTree/main.o -o segment_tree.exe

clean:	
	rm FenwickTree/fenwick_tree.o FenwickTree/main.o
	rm TestGenerator/create_array.o TestGenerator/create_requests.o