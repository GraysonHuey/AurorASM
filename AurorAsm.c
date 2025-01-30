#include <stdio.h>
#include <string.h>
#include <assert.h>


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

void usage() {
    printf("[ERROR]: Incorrect command usage!\n");
    printf("Correct usage: %s <file.aur> [output name]\n");
    printf("    file.aur: REQUIRED file path to compile\n");
    printf("    output name: OPTIONAL name to give the compiled binary\n");
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        usage();
        return 1;
    }

    char** output_name = "output";
    if (argc == 3) {
        output_name = argv[2];
    }

    char** file_name = argv[1];
    if (strcmp(FileSuffix(file_name), ".aur") != 0) {
        printf("[ERROR]: Aurora (.aur) file not provided!\n");
        return 1;
    }
}
