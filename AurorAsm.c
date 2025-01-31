#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 256
#define MAX_LINE_LENGTH 256

#define RED "\x1b[31m"
#define RESET "\x1b[39m"

const char* FileSuffix(const char path[]) {
    const char* result;
    int i, n;

    assert(path != NULL);
    n = strlen(path);
    i = n-1;
    while ((i > 0) && (path[i] != '.') && (path[i] != '/') && (path[i] != '\\')) {
        i--;
    }
    if ((i > 0) && (i < n - 1) && (path[i] == '.') && (path[i - 1] != '/') && (path[i - 1] != '\\')) {
        result = path + i;
    } else {
        result = path + n;
    }
    return result;
}

int readFile(const char* file_path, char buf[MAX_LINES][MAX_LINE_LENGTH]) {
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("%s[ERROR]: Error opening file%s\n", RED, RESET);
        return -2;
    }

    int i = 0;
    while (i < MAX_LINES && fgets(buf[i], MAX_LINE_LENGTH, fp)) {
        buf[i][strcspn(buf[i], "\n")] = '\0';
        i++;
    }
    fclose(fp);

    return i;
}

void usage(char** argv) {
    printf("%s[ERROR]: Incorrect command usage!\n", RED);
    printf("Correct usage: %s <file.aur> [output name]\n", argv[0]);
    printf("    file.aur: REQUIRED file path to compile\n");
    printf("    output name: OPTIONAL name to give the compiled binary%s\n", RESET);
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        usage(argv);
        return 1;
    }

    char* output_name = "output";
    if (argc == 3) {
        output_name = argv[2];
    }

    char* file_name = argv[1];
    if (strcmp(FileSuffix(file_name), ".aur") != 0) {
        printf("[ERROR]: Aurora (.aur) file not provided!\n");
        return 1;
    }

    char file_contents[MAX_LINES][MAX_LINE_LENGTH];
    int lines_read = readFile(file_name, file_contents);

    if (lines_read == -1) {
        printf("[ERROR]: No lines read from file. Ensure the file has contents and try again");
        return 1;
    } else if (lines_read == -2) {
        return 1;
    }

    for (int i = 0; i != lines_read; i++) {
        printf("[LOG]: %s\n", file_contents[i]);
    }

    return 0;
}
