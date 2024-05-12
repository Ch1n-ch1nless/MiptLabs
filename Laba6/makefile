CC=gcc

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
	$(CC) $(CFLAGS) TestGenerator/create_test.cpp -o TestGenerator/create_test.exe
	$(CC) $(CFLAGS) TestGenerator/create_sorted_test.cpp -o TestGenerator/create_sorted_test.exe
	chmod +x TestGenerator/generate_tests.sh
	./TestGenerator/generate_tests.sh

create_bst:
	$(CC) $(CFLAGS) -c BinarySearchTree/main.cpp -o BinarySearchTree/main.o
	$(CC) $(CFLAGS) -c BinarySearchTree/binary_tree.cpp -o BinarySearchTree/binary_tree.o
	$(CC) BinarySearchTree/main.o BinarySearchTree/binary_tree.o -o binary_tree.exe

create_avl:
	$(CC) $(CFLAGS) -c AVLTree/main.cpp -o AVLTree/main.o
	$(CC) $(CFLAGS) -c AVLTree/avl_tree.cpp -o AVLTree/avl_tree.o
	$(CC) AVLTree/main.o AVLTree/avl_tree.o -o avl_tree.exe

create_trp:
	$(CC) $(CFLAGS) -c Treap/main.cpp -o Treap/main.o
	$(CC) $(CFLAGS) -c Treap/treap.cpp -o Treap/treap.o
	$(CC) Treap/main.o Treap/treap.o -o treap.exe

create_splay:
	$(CC) $(CFLAGS) -c SplayTree/main.cpp -o SplayTree/main.o
	$(CC) $(CFLAGS) -c SplayTree/splay_tree.cpp -o SplayTree/splay_tree.o
	$(CC) SplayTree/main.o SplayTree/splay_tree.o -o splay_tree.exe
