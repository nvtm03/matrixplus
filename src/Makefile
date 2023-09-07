CC = g++ 
CFLAGS = -std=c++17 -Wall -Wextra -Werror
OS := $(shell uname -s)
SRC = s21_matrix_oop.cpp
OBJ = $(SRC:.cpp=.o)
TESTFILES = test.cpp
TESTFLAGS = -lgtest

all: s21_matrix_oop.a test


s21_matrix_oop.a: clean
		$(CC) $(CFLAGS) $(SRC) -c 
		ar rcs s21_matrix_oop.a *.o

test:
	$(CC) $(TESTFILES) $(TESTFLAGS) $(CFLAGS) s21_matrix_oop.cpp  -o test
	./test
	# $(CC) $(CFLAGS) -gtest $(SRC) test.cpp -o test -g

clean:
	rm -rf test build
	rm -rf *.a *.o

rebuild:
	make clean
	make all

style:
	clang-format -n -style=Google s21_matrix_oop.cpp
	clang-format -n -style=Google s21_matrix_oop.h
	clang-format -n -style=Google s21_matrix_oop.h
