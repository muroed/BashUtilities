#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <pcre.h>

typedef struct mod {
    int e;
    int i;
    int v;
    int c;
    int n;
    int l;
    int error;
}mod;


void take_mod(mod* flag, short parm);
int strcompared(char* str, char** sample, int sample_number, mod flag);

int main(int argc, char* argv[]) {
    mod flag;
    flag.error = 0;
    take_mod(&flag, 0);
    short sample_number = 0;
    FILE* fp;

    char* sample[1000];

    int str_number = 0;
    int str_number_in_file = 0;
    int rez = 0;
    opterr = 0;


    // const char* short_options = "e:ivcln";

    // struct option long_options[] = {
    //     { "opte", required_argument, &flag.e, 1 },
    //     { "opti", no_argument, &flag.i, 1 },
    //     { "optv", no_argument, &flag.v, 1 },
    //     { "optc", no_argument, &flag.c, 1 },
    //     { "optn", no_argument, &flag.n, 1 },
    //     { "optl", no_argument, &flag.l, 1 },
    //     { NULL, 0, NULL, 0}
    // };

    while ((rez = getopt_long(argc, argv, "e: i v c l n", NULL, NULL)) != -1) {
    // while ((rez = getopt(argc + 1, argv, "e: i v c l n")) != -1) {
        switch (rez) {
            case 'e': flag.e = 1;
                    // sample = realloc(sample, sizeof(char*) + 1);
                    sample[sample_number] = optarg;
                    sample_number++;
                    break;
            case 'i': flag.i = 1;
            break;
            case 'v': flag.v = 1;
            break;
            case 'c': flag.c = 1;
            break;
            case 'l': flag.l = 1;
            break;
            case 'n': flag.n = 1;
            break;
        }
    }

    if (!flag.e) {
        sample[0] = argv[optind];
        sample_number++;
    }

    for (int i = optind + (!flag.e ? 1 : 0); i < argc; i++) {
        char* file_name = argv[i];
        if ((fp = fopen(file_name, "r")) != NULL) {
            str_number = 0;
            str_number_in_file = 0;
            char string[1024];
                while (!feof(fp)) {
                    if (fgets(string, 1024, fp)) {
                        str_number_in_file++;
                        if (strcompared(string, sample, sample_number, flag)) {
                            str_number++;
                    //  Print filename if number is greater than 2
                        if (!flag.c && !flag.l) {
                            if (argc - optind + sample_number - 1 > 2) printf("%s:", file_name);
                            if (flag.n) printf("%d:", str_number_in_file);
                            if (string[strlen(string) - 1] == '\n') printf("%s", string);
                            else
                            printf("%s\n", string);
                        }
                    }
                }
            }
            if (flag.c) {
                if (argc - optind + sample_number - 1 > 2) printf("%s:", file_name);
                if (flag.l && str_number > 0) str_number = 1;
                printf("%d\n", str_number);
            }
            if (flag.l && str_number > 0) printf("%s\n", file_name);
            fclose(fp);
        } else {if (file_name[0] != '-') fprintf(stdout, "%s:file does not exist\n", file_name);}
    }
}


void take_mod(mod* flag, short parm) {
    flag->e = parm;
    flag->i = parm;
    flag->v = parm;
    flag->c = parm;
    flag->n = parm;
    flag->l = parm;
}

int strcompared(char* str, char** sample, int sample_number, mod flag) {  // -i and -v flags
    int res = (!flag.v ? 0 : 1);
    pcre *re;
    int option = 0;
    const char* error;
    int erroffset;
    int ovector[30];
    for (int i = 0; i < sample_number; i++)
    if (!flag.i) {
        re = pcre_compile(sample[i], option, &error, &erroffset, NULL);
        if (re)
            if (pcre_exec(re, NULL, str, strlen(str), 0, 0, ovector, 30) > 0) res = (!flag.v ? 1 : 0);
        pcre_free(re);
    } else {
        char sample_i[1024];  // = malloc(sizeof(char) * (strlen(str) + 4));
        strcpy(sample_i, "(?i)");
        strcat(sample_i, sample[i]);
        re = pcre_compile(sample_i, option, &error, &erroffset, NULL);
        if (re)
            if (pcre_exec(re, NULL, str, strlen(str), 0, 0, ovector, 30) > 0) res = (!flag.v ? 1 : 0);
        // free(sample_i);
        pcre_free(re);
    }
    return res;
}
