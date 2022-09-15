#ifndef SRC_COMMON_S21_CAT_H_
#define SRC_COMMON_S21_CAT_H_

typedef struct mod {
    short e;
    short b;
    short n;
    short t;
    short s;
    short v;
}mod;

void take_mod(mod *flag, short parm);
void work_cat(int argc, char *argv[], mod flag);
mod parser(int argc, char* argv[]);
void verbose(unsigned char ch);


#endif  //  SRC_COMMON_S21_CAT_H_