#include <stdio.h>
#include <string.h>
#include "s21_cat.h"

int main(int argc, char* argv[]) {
    mod flag = parser(argc, argv);
    work_cat(argc, argv, flag);
    return 0;
}
