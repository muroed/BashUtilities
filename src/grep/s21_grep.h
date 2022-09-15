#ifndef SRC_COMMON_S21_GREP_H_
#define SRC_COMMON_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <string.h>
#include <getopt.h>

typedef struct mod {
    short e;
    short i;
    short v;
    short c;
    short n;
    short l;
    short h;
    short f;
    short s;
    short o;
}mod;

void print_d(int n);
void print_p(char* str);
void print_n(char* str);
void print(char* str);
void option_n(mod flag, int num);
void filename(int argc, mod flag, char* name);
char* add_sample(char* sample, char* str);
char* option_f(char* file_name, char *sample, mod *flag);
void take_mod(mod *flag);
int strcompared(char* str, char* sample, mod flag, int argc, char* name, int num_str);
int parser(char **argv, int argc, mod *flag, char* sample);
void work_grep(char** argv, int argc, mod flag, char* sample);

#endif  //  SRC_COMMON_S21_GREP_H_