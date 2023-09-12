#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_WORDS_PER_CHUNK 250000

int _calc_file_length(FILE* fp);

int _calc_file_length(FILE* fp){
    int file_length = 0;
    char str[100];
    while (fscanf(fp, "%s\n", str) != EOF) {
        file_length++;
    }
    return file_length;
}

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
    int file_length = _calc_file_length(fp);
    int num_chunks = file_length / NUM_WORDS_PER_CHUNK;
    // split file into chunks
    for (int i = 0; i < num_chunks; i++){
        char* chunk_file_path = malloc(sizeof(char) * 100);
        sprintf(chunk_file_path, "chunk_%d.txt", i);
        FILE* chunk_fp = fopen(chunk_file_path, "w");
        if (chunk_fp == NULL) {
            printf("Error opening file %s", chunk_file_path);
            return 1;
        }
        char str[100];
        int accum = 0;
        while(fgets(str, 100, fp) != NULL && accum < NUM_WORDS_PER_CHUNK){
            fputs(str, chunk_fp);
            accum++;
        }
        free(chunk_file_path);
        fclose(chunk_fp);
    }

    fclose(fp);
    printf("%d", num_chunks);
    return 0;
}