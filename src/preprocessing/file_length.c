#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    if (argc < 2){
        return 1;
    }

    char* file_path = argv[1];

    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file %s", file_path);
        return 1;
    }
    
    long file_length = 0;
    char str[100];
    while (fscanf(fp, "%s\n", str) != EOF) {
        file_length++;
    }
    printf("%ld",file_length);
    return 0;
}