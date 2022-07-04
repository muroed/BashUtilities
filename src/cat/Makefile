CC:=gcc
BASH:=cat
SANITIZER:= #-fsanitize=address
CFLAGS:= $(SANITIZER) -Wall -Werror -Wextra -std=c11
SOURCE:= s21*.c
TEST_FILE:=../test/text2.txt ../test/text1.txt
TEST_FLAGS:=-bes	
TEST:=$(BASH) $(TEST_FLAGS) $(TEST_FILE)

all: check build

build: clean s21_$(BASH)

s21_$(BASH):
	$(CC)  $(CFLAGS) s21_$(BASH).c -o s21_$(BASH)

auto_test: clean build
	bash test_$(BASH).sh

test: build
	$(TEST)
	./s21_$(TEST)

clean:
	rm -f s21_$(BASH)
	rm -f log_$(BASH).txt
	rm -f CPPLINT.cfg

check: ${SOURCE}
ifeq ("","$(wildcard ./CPPLINT.cfg)")
	cp -f ../../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
endif
	!(python3 ../../materials/linters/cpplint.py --extensions=c $^ | grep -q :)

leaks: build
	leaks -atExit -- ./s21_$(TEST)

