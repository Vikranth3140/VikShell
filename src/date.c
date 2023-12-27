#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int d_flag = 0;
int R_flag = 0;

void last_time(const char *filename) {
    struct stat fileInfo;

    if (stat(filename, &fileInfo) == 0) {
        char time_format[100];

        if (d_flag || (!d_flag && !R_flag)) {
            strftime(time_format, sizeof(time_format), "%a %b %d %I:%M:%S %p %Z %Y", localtime(&fileInfo.st_mtime));
            printf("Last modified date and time = %s\n", time_format);
        }

        if (R_flag) {
            strftime(time_format, sizeof(time_format), "%a %d %b %Y %I:%M:%S %z", localtime(&fileInfo.st_mtime));
            printf("Last modified date and time (RFC 5322) = %s\n", time_format);
        }

    } else {
        printf("Error: Invalid Command\n");
    }
}

int main(int argc, char *argv[]) {
    int opt;
    int option_count = 0;

    while ((opt = getopt(argc, argv, "dR")) != -1) {
        switch (opt) {
            case 'd':
                d_flag = 1;
                option_count++;
                break;
            case 'R':
                R_flag = 1;
                option_count++;
                break;
            default:
                printf("Error: Invalid command\n");
                return 1;
        }
    }

    if (option_count > 1) {
        printf("Error: Invalid command\n");
        return 1;
    }

    if (optind >= argc) {
        printf("Syntax: %s [-option] [file_name]\n", argv[0]);
        return 1;
    }

    const char *file = argv[optind];
    last_time(file);

    return 0;
}