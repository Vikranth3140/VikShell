#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int n_flag = 0;
int d_flag = 0;

typedef struct Wordcount {
    int word_n;
    int def_main;
} Wordcount;

Wordcount word_count(const char *filename) {

    FILE *file;
    file = fopen(filename, "r");

    int words = 0;
    int n = 0;

    if (file == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') {
            words++;
            if (ch == '\n') {
                n++;
            }
        }
    }

    fclose(file);

    Wordcount values;
    values.word_n = words;
    values.def_main = n + words;

    return values;
}

int word_count_difference(const char *filename1, const char *filename2){

    Wordcount word_1 = word_count(filename1);
    Wordcount word_2 = word_count(filename2);

    int diff = abs(word_1.word_n - word_2.word_n);

    return diff;
}


int main(int argc, char *argv[]) {

    int opt;
    int option_count = 0; 
    char *filename1;
    char *filename2;

    while ((opt = getopt(argc, argv, "nd")) != -1) {
        switch (opt) {
            case 'n':
                n_flag = 1;
                option_count++;
                break;
            case 'd':
                d_flag = 1;
                option_count++;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n] <filename>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (option_count > 1) {
        fprintf(stderr, "Error: Invalid command\n");
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        filename1 = argv[optind];
        optind++;

    } else {
        fprintf(stderr, "Usage: %s [-n] [-d] <filename1> [filename2]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        filename2 = argv[optind];
    }

    if (d_flag) {
        if (filename2 == NULL) {
            fprintf(stderr, "Usage: %s -d <filename1> <filename2>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        int diff = word_count_difference(filename1, filename2);
        printf("Word count difference between %s and %s: %d\n", filename1, filename2, diff);
    }
    else{

        Wordcount result = word_count(filename1);

        if (n_flag) {

            printf("Word count (-n) for file %s: %d\n", filename1, result.word_n);

        } else {

            printf("Word count (default) for file %s: %d\n", filename1, result.def_main);
            
        }
    }

    return 0;
}