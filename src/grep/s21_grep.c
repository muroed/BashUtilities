#include "s21_grep.h"

int main(int argc, char* argv[]) {
    mod flag;
    take_mod(&flag);
    char sample[500];
    sample[0] = '\0';

    parser(argv, argc, &flag, sample);
    work_grep(argv, argc, flag, sample);
}
