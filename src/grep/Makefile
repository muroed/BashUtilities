CC:=gcc
BASH:=grep
SANITIZER:= #-fsanitize=address
CFLAGS:= $(SANITIZER) -Wall -Werror -Wextra -std=c11
LFLAGS:=-L. -lbash
SOURCE:=addition_$(BASH).c
OBJECT := addition_$(BASH).o
LIN_FLAGS := -lpthread -pthread -lrt -lm
ifeq ($(shell uname), Linux)
LFLAGS += $(LIN_FLAGS)
endif
TEST_FILE:=
TEST_FLAGS:= -v -e dolor -e grep ../test/text1.txt ../test/text2.txt
TEST:=$(BASH) $(TEST_FLAGS) $(TEST_FILE)

all: check build
build: clean clean_lib s21_$(BASH)

s21_bash: $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar rc libbash.a $(OBJECT)
	ranlib libbash.a

s21_$(BASH): s21_bash
	$(CC) $(CFLAGS) s21_$(BASH).c -o s21_$(BASH) $(LFLAGS)

test: clean build
	@sh test_$(BASH).sh

my_test: build
	$(TEST)
	./s21_$(TEST)

clean: clean_lib
	@rm -f s21_$(BASH)
	@rm -f log_$(BASH).txt
	rm -f CPPLINT.cfg
	rm -f *.o

clean_lib:
	rm -f libbash.a
	rm -f $(OBJECT)

check: $(SOURCE)
ifeq ("","$(wildcard ./CPPLINT.cfg)")
	cp -f ../../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
endif
	!(python3 ../../materials/linters/cpplint.py --extensions=c $^ | grep -q :)

leaks: build
	leaks -atExit -- ./s21_$(TEST)
valgrind: build
	valgrind ./s21_$(TEST) 
val: build
	bash test_valgrind.sh > valgrind.txt
	grep -n -e "^Process.[0-9]"  valgrind.txt
	rm -f valgrind.txt
