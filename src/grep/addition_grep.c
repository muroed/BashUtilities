#include "s21_grep.h"
#include <regex.h>

#define MAX_MATCHES  100

void take_mod(mod *flag) {
    flag->e = 0;
    flag->i = 0;
    flag->v = 0;
    flag->c = 0;
    flag->n = 0;
    flag->l = 0;
    flag->h = 0;
    flag->f = 0;
    flag->s = 0;
    flag->o = 0;
}

int parser(char **argv, int argc, mod *flag, char* sample) {
    opterr = 0;
    int rez = 0;
    while ((rez = getopt_long(argc, argv, "e: i v c l n h s o f:", NULL, NULL)) != -1) {
        switch (rez) {
            case 'e': flag->e = 1;
                    sample = add_sample(sample, optarg);
                    break;
            case 'i': flag->i = 1;
            break;
            case 'v': flag->v = 1;
            break;
            case 'c': flag->c = 1;
            break;
            case 'l': flag->l = 1;
            break;
            case 'n': flag->n = 1;
            break;
            case 'h': flag->h = 1;
            break;
            case 's': flag->s = 1;
            break;
            case 'o': flag->o = 1;
            break;
            case 'f': flag->f = 1;
                        sample = option_f(optarg, sample, flag);
                        break;
        }
    }
    if (flag->v == 1 && flag->o == 1) flag->o = 0;
    return optind;
}

int strcompared(char* str, char* sample, mod flag, int argc, char* name, int num_str) {
    int res = (!flag.v ? 0 : 1);
    char* str_ = str;
    regex_t re;
    int err, regerr;

    char *sample_i = malloc(sizeof(char) * strlen(sample) + 7);
    strcpy(sample_i, sample);
    if (flag.i)
        err = regcomp(&re, sample_i, REG_EXTENDED|REG_ICASE);
    else
        err = regcomp(&re, sample_i, REG_EXTENDED);
    if (err == 0) {
        regmatch_t pm[MAX_MATCHES];
        if ((regerr = regexec(&re, str, MAX_MATCHES, pm, 0)) == 0) {
            res = (!flag.v ? 1 : 0);

            if (flag.o == 1 && regerr == 0 && flag.c == 0 && flag.l == 0) {
                do {
                   if (flag.c == 0 && flag.l == 0) {
                        if (str == str_) {
                            filename(argc, flag, name);
                            option_n(flag, num_str);
                        }
                    }
                    for (int i = pm[0].rm_so; pm[0].rm_so >= 0 && i < pm[0].rm_eo; i++) printf("%c", str[i]);
                    printf("\n");
                    str += pm[0].rm_eo;
                } while (strlen(str) > 0 && (regerr = regexec(&re, str, MAX_MATCHES, pm, 0)) == 0);
            }
        }
    }
    regfree(&re);
    free(sample_i);
    return res;
}



char *add_sample(char *sample, char *str) {
    if (strlen(sample) == 0) {
        strcpy(sample, str);
    } else if (str) {
        strncat(sample, "|", 2);
        strncat(sample, str, strlen(str));
    }
    return sample;
}

char *option_f(char* file_name, char *sample, mod* flag) {
    FILE *fp;
    if ((fp = fopen(file_name, "r")) != NULL) {
        char sample_from_file[1024];
        while (!feof(fp)) {
            fscanf(fp, "%s\n", sample_from_file);
            sample = add_sample(sample, sample_from_file);
        }
    } else {if (!flag->s) fprintf(stdout, "%s:file does not exist\n", file_name);}
    fclose(fp);
    return sample;
}


void work_grep(char** argv, int argc, mod flag, char* sample) {
    FILE* fp;
    int str_number_in_file = 0;

    if (flag.e == 0 && flag.f == 0) {
        sample = add_sample(sample, argv[optind]);
    }

    for (int i = optind + (!flag.e && !flag.f ? 1 : 0); i < argc; i++) {
        char* file_name = argv[i];
        if ((fp = fopen(file_name, "r")) != NULL) {
        unsigned int str_number = 0;
        str_number_in_file = 0;
            char string[1024];
            while (!feof(fp)) {
                if (fgets(string, 1024, fp)) {
                    str_number_in_file += 1;
                    if (strcompared(string, sample, flag, argc, file_name, str_number_in_file)) {
                            str_number++;
                        if (!flag.c && !flag.l && !flag.o) {
                                filename(argc, flag, file_name);
                                option_n(flag, str_number_in_file);
                                if (string[strlen(string) - 1] == '\n') print(string);
                                else
                                print_n(string);
                        }
                    }
                }
            }
            if (flag.c) {
                filename(argc, flag, file_name);
                if (flag.l == 1 && str_number > 0 ) str_number = 1;
                print_d(str_number);
                printf("\n");
            }
            if (flag.l && str_number > 0) print_n(file_name);
            fclose(fp);
        } else {if (file_name[0] != '-' && !flag.s) fprintf(stdout, "%s:file does not exist\n", file_name);}
    }
}
void print_p(char* str) {
    printf("%s:", str);
}

void print_n(char* str) {
    printf("%s\n", str);
}

void print(char* str) {
    printf("%s", str);
}

void option_n(mod flag, int num) {
    if (flag.n) {
        print_d(num);
        printf(":");
    }
    flag.n = 1;
}
void print_d(int n) {
    printf("%d", n);
}
void filename(int argc, mod flag, char* name) {
    if (argc - optind - (flag.e || flag.f? 0 : 1) >= 2 && !flag.h)
        print_p(name);
}
