#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void format_text(char* file_path, char* output_file_path);

void format_text(char* file_path, char* output_file_path){
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file %s", file_path);
        return;
    }

    FILE* output_fp = fopen(output_file_path, "w");
    if (output_fp == NULL) {
        printf("Error opening file %s", output_file_path);
        return;
    }

    char str[100];
    while (fscanf(fp, "%s\n", str) != EOF) {
        char* token = strtok(str, " ");
        while(token != NULL){
            fprintf(output_fp, "%s\n", token);
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);
    fclose(output_fp);
}

int main(int argc, char** argv){
    if (argc != 3){
        printf("Usage: ./text_format_script <input_file_path> <output_file_path>\n");
        return 1;
    }
    format_text(argv[1], argv[2]);
    return 0;
}