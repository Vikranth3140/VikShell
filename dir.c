#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h> 

int r_flag = 0;
int v_flag = 0;

void dir(const char *dirname) {

    char currentDir[100]; 
    if (r_flag) {
        if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
            struct stat st;
            if (stat(dirname, &st) == 0 && S_ISDIR(st.st_mode)) {
                if (rmdir(dirname) != 0) {
                    perror("rmdir");
                    exit(1);
                }
                if (v_flag) {
                    printf("Removed existing directory: %s\n", dirname);
                }
            }
        } else {
            perror("getcwd");
            exit(1);
        }
    }

    struct stat st;
    if (stat(dirname, &st) == 0 && S_ISDIR(st.st_mode)) {
        if (!r_flag) {
           
            exit(1);
        }
    } else {
        int check = mkdir(dirname, 0777);
        if (check == 0) {
            if (v_flag) {
                printf("Directory created: %s\n", dirname);
            }
            if (chdir(dirname) != 0) {
                perror("chdir");
                exit(1);
            }
            if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
                if (v_flag) {
                    printf("Changed current working directory to: %s\n", currentDir);
                }
            } else {
                perror("getcwd");
                exit(1);
            }
        } else {
            printf("Unable to create directory\n");
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;
    
    while ((opt = getopt(argc, argv, "rv")) != -1) {
        switch (opt) {
            case 'r':
                r_flag = 1;
                v_flag = 1; // Set v_flag to 1 when -r is used
                break;
            case 'v':
                v_flag = 1;
                break;
            default:
                fprintf(stderr, "Invalid command\n");
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Invalid command\n");
        exit(EXIT_FAILURE);
    }

    const char *dirname = argv[optind];

    dir(dirname);

    return 0;
}