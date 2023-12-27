#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ncurses.h>
#include <dirent.h>

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
        printf("Error: Invalid command\n");
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

int word_count_difference(const char *filename1, const char *filename2) {
    Wordcount word_1 = word_count(filename1);
    Wordcount word_2 = word_count(filename2);

    int diff = abs(word_1.word_n - word_2.word_n);

    return diff;
}

void executeExternalCommand(const char *command, char *const args[]) {
    int pid = fork();

    if (pid == 0) {
        execvp(command, args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}

void listFiles(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printw("%s\n", entry->d_name);
        refresh();
    }

    closedir(dir);
}

void printVikShell() {
    clear();

    printw(
        "  _____ _           _      _____ _           _\n"
        " |  __ (_)         | |    / ____| |         | |\n"
        " | |__) | ___  __ _| |_  | (___ | |__   __ _| |\n"
        " |  ___/ |/ _ \\/ _` | __|  \\___ \\| '_ \\ / _` | |\n"
        " | |   | |  __/ (_| | |_   ____) | | | | (_| | |\n"
        " |_|   |_|\\___|\\__,_|\\__| |_____/|_| |_|\\__,_|_|\n\n"
        "Welcome to VikShell!\n\n"
        "To get started, you can try the following commands:\n"
        "- Type 'help' for a list of available commands.\n"
        "- Explore basic Linux commands such as 'ls', 'cd', 'mkdir', 'dir', 'word', 'date'.\n"
        "- If you want to exit VikShell, type 'exit'.\n\n"
    );
    refresh();
}

void printHelp() {
    printw(
        "\nAvailable Commands:\n"
        "- help: Display this help message.\n"
        "- ls: List files and directories.\n"
        "- cd <directory>: Change current directory.\n"
        "- mkdir <directory>: Create a new directory.\n"
        "- dir [-r] [-v] <directory>: Create or remove a directory.\n"
        "- word [-n | -d] <filename1> [filename2]: Count words in files.\n"
        "- date: Display current date and time.\n"
        "- exit: Exit VikShell.\n\n"
    );
    refresh();
}

int main() {
    char input[100];

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    printVikShell();

    while (1) {
        printw("\nVikShell> ");
        getnstr(input, sizeof(input) - 1);

        char *token = strtok(input, " ");

        if (token != NULL) {
            if (strcmp(token, "dir") == 0) {
                char *dir_cmd[3];
                dir_cmd[0] = "./dir";
                dir_cmd[1] = NULL;
                dir_cmd[2] = NULL;
                dir_cmd[3] = NULL;

                token = strtok(NULL, " ");
                if (token != NULL) {
                    if (strcmp(token, "-r") == 0 || strcmp(token, "-v") == 0) {
                        dir_cmd[1] = token;
                        token = strtok(NULL, " ");
                        if (token != NULL) {
                            dir_cmd[2] = token;
                        }
                    } else {
                        dir_cmd[2] = token;
                    }
                }
                executeExternalCommand(dir_cmd[0], dir_cmd);

            } else if (strcmp(token, "date") == 0) {
                char *date_cmd[3];

                date_cmd[0] = "./date";
                date_cmd[1] = input;
                date_cmd[2] = NULL;
                date_cmd[3] = NULL;

                executeExternalCommand(date_cmd[0], date_cmd);

            } else if (strcmp(token, "word") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    if (strcmp(token, "-n") == 0) {
                        token = strtok(NULL, " ");
                        if (token != NULL) {
                            Wordcount result = word_count(token);
                            printw("Word count (-n) for file %s: %d\n", token, result.word_n);
                        } else {
                            printw("Error: Invalid command\n");
                        }
                    } else if (strcmp(token, "-d") == 0) {
                        char *filename1 = strtok(NULL, " ");
                        char *filename2 = strtok(NULL, " ");
                        if (filename1 != NULL && filename2 != NULL) {
                            int diff = word_count_difference(filename1, filename2);
                            printw("Word count difference between %s and %s: %d\n", filename1, filename2, diff);
                        } else {
                            printw("Error: Invalid command\n");
                        }
                    } else {
                        Wordcount result = word_count(token);
                        printw("Word count (default) for file %s: %d\n", token, result.def_main);
                    }
                } else {
                    printw("Error: Invalid command\n");
                }
            } else if (strcmp(token, "cd") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    if (chdir(token) == 0) {
                        printw("Changed directory to: %s\n", token);
                    } else {
                        printw("Error: Unable to change directory to: %s\n", token);
                    }
                } else {
                    printw("Error: Invalid command\n");
                }
            } else if (strcmp(token, "mkdir") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    if (mkdir(token, 0777) == 0) {
                        printw("Directory created: %s\n", token);
                    } else {
                        printw("Error: Unable to create directory: %s\n", token);
                    }
                } else {
                    printw("Error: Invalid command\n");
                }
            } else if (strcmp(token, "ls") == 0) {
                char *ls_cmd[3];
                ls_cmd[0] = "ls";
                ls_cmd[1] = NULL;
                ls_cmd[2] = NULL;
                ls_cmd[3] = NULL;

                token = strtok(NULL, " ");
                if (token != NULL) {
                    ls_cmd[1] = token;
                }
                executeExternalCommand(ls_cmd[0], ls_cmd);
            } else if (strcmp(token, "help") == 0) {
                printHelp();
            } else if (strcmp(token, "exit") == 0) {
                printw("Exiting custom shell.\n");
                break;
            } else {
                printw("Unknown command: %s\n", input);
            }
        }
    }

    endwin();

    return 0;
}