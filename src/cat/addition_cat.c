#include "s21_cat.h"
#include <stdio.h>
#include <string.h>


void take_mod(mod *flag, short parm) {
    int i = 0;
    short *take = &(flag->e);
    while (i < (int)sizeof(flag)) {
        *take = parm;
        take++;
        i++;
    }
}


void verbose(unsigned char ch) {
    if (ch < 32) {
            if (ch == 9) {
                printf("\t");
            } else if (ch == 10 && ch != 0) {
                printf("\n");
            } else {
                printf("^%c", ch + 64);
            }
        } else if (ch >= 32 && ch < 128) {
            if (ch == 127) {
                printf("^%c", ch - 64);
            } else {
                printf("%c", ch);
            }
        } else if (ch >= 128 && ch < (128 + 32)) {
            printf("M-^%c", ((int)ch - 64));

        } else {
           printf("%c", ch);
        }
}


void work_cat(int argc, char *argv[], mod flag) {
    FILE* fp;
    int count_str = 1;
    for (int i = 1; i < argc; i++) {
        char *str = argv[i];
        if (*str != '-') {
            if ((fp = fopen(str, "r")) != NULL) {
                char ch, ch_next;
                int number_n = 0;
                count_str = 1;
                short start = 0;
                if (!flag.b && flag.n) printf("%6d\t", count_str++);
                if (flag.b && (ch_next = fgetc(fp)) != EOF) {
                    fseek(fp, -1, SEEK_CUR);
                    if (ch_next != '\n') printf("%6d\t", count_str++);
                }
                while ((ch = fgetc(fp)) != EOF) {
                    if (flag.s && ch == '\n') {
                        if ((ch_next = fgetc(fp)) != EOF) {
                            fseek(fp, -1, SEEK_CUR);
                            if (ch_next == '\n') number_n++;
                            if (ch_next != '\n') number_n = 0;
                            if (ch_next == '\n' && number_n > 1 && start != 0) continue;
                            if (ch_next == '\n' && number_n >= 1 && start == 0) continue;
                        }
                    }

                    if (flag.e && ( ch == '\n')) printf("$");

                    if (flag.t && ch == '\t') {
                        printf("^");
                        ch = 'I';
                    }

                     if (flag.v) {
                        verbose(ch);
                     } else {
                        printf("%c", ch);
                     }

                    if (flag.b && ch == '\n') {
                        if ((ch_next = fgetc(fp)) != EOF) {
                            if (ch_next != '\n') {
                                printf("%6d\t", count_str++);
                            }
                            fseek(fp, -1, SEEK_CUR);
                        }
                    }

                    if (flag.n && !flag.b && ch == '\n' && (ch_next = fgetc(fp)) != EOF) {
                        printf("%6d\t", count_str++);
                        fseek(fp, -1, SEEK_CUR);
                    }
                    if (start == 0) start = 1;
                }
            fclose(fp);
            }
        }
    }
}

mod parser(int argc, char* argv[]) {
    char* str;
    mod flag;
    take_mod(&flag, 0);
for (int i = 1; i < argc; i++) {
        str = argv[i];
        if (*str == '-') {
            str++;
            for (; *str; str++) {
                if (*str == '-') {
                    if (strcmp(str, "-number") == 0) flag.n = 1;

                    if (strcmp(str, "-number-nonblank") == 0) flag.b = 1;

                    if (strcmp(str, "-squeeze-blank") == 0) flag.s = 1;

                    break;
                } else {
                if (*str == 'b') flag.b = 1;

                if (*str == 'n') flag.n = 1;

                if (*str == 'e') {
                    flag.e = 1;
                    flag.v = 1;
                }

                if (*str == 'E') flag.e = 1;

                if (*str == 'T') flag.t = 1;

                if (*str == 't') {
                    flag.t = 1;
                    flag.v = 1;
                }

                if (*str == 'v') flag.v = 1;
                if (*str == 's') flag.s = 1;
                }
            }
        }
    }
    return flag;
}
