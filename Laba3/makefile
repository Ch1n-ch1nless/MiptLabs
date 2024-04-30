CC=g++

CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal\
       -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
       -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions\
	   -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security\
	   -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor\
	   -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
	   -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla\
	   -D_DEBUG -g

all:	test_generate

test_generate:
	$(CC) $(CFLAGS) TestGenerator/create_random_array.c -o TestGenerator/create_random_array.exe
	$(CC) $(CFLAGS) TestGenerator/qsort_random_array.c -o TestGenerator/qsort_random_array.exe
	chmod +x TestGenerator/very_small_tests.sh
	./TestGenerator/very_small_tests.sh
	chmod +x TestGenerator/small_tests.sh
	./TestGenerator/small_tests.sh
	chmod +x TestGenerator/big_tests.sh
	./TestGenerator/big_tests.sh
	chmod +x TestGenerator/test_most_dublicates.sh
	./TestGenerator/test_most_dublicates.sh

punct1:
	$(CC) $(CFLAGS) -c Punct#1/quadratic_sorts.c -o Punct#1/quadratic_sorts.o
	$(CC) $(CFLAGS) -c Punct#1/shell_sort.c -o Punct#1/shell_sort.o
	$(CC) $(CFLAGS) -c Punct#1/main.c -o Punct#1/main.o
	$(CC) Punct#1/main.o Punct#1/quadratic_sorts.o Punct#1/shell_sort.o -o test_punct1.exe

punct2:
	$(CC) $(CFLAGS) -c Punct#2/heap_sort.c -o Punct#2/heap_sort.o
	$(CC) $(CFLAGS) -c Punct#2/main.c -o Punct#2/main.o
	$(CC) Punct#2/main.o Punct#2/heap_sort.o -o test_punct2.exe

punct3:
	$(CC) $(CFLAGS) -c Punct#3/merge_sort.c -o Punct#3/merge_sort.o
	$(CC) $(CFLAGS) -c Punct#3/main.c -o Punct#3/main.o
	$(CC) -g Punct#3/main.o Punct#3/merge_sort.o -o test_punct3.exe

punct4:
	$(CC) $(CFLAGS) -c Punct#4/quick_sort_partition.c -o Punct#4/quick_sort_partition.o
	$(CC) $(CFLAGS) -c Punct#4/main.c -o Punct#4/main.o
	$(CC) -g Punct#4/main.o Punct#4/quick_sort_partition.o -o test_punct4.exe

punct5:
	$(CC) $(CFLAGS) -c Punct#5/quick_sort_pivot_choice.c -o Punct#5/quick_sort_pivot_choice.o
	$(CC) $(CFLAGS) -c Punct#5/main.c -o Punct#5/main.o
	$(CC) -g Punct#5/main.o Punct#5/quick_sort_pivot_choice.o -o test_punct5.exe

clean:
	rm *.o