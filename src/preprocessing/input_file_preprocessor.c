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
    for (int i = 0; i < argc; i++){
        FILE* fp = fopen(file_path, "r");
        if (fp == NULL) {
            printf("Error opening file %s", file_path);
            return 1;
        }

        int file_length = _calc_file_length(fp);
        char** word_arr = malloc(sizeof(char*) * file_length);
        char str[100];
        // read all words into array
        for (int i = 0; i < file_length; i++) {
            fscanf(fp, "%s\n", str);
            word_arr[i] = strdup(str);
        }
        fclose(fp);
        // divide array into chunks based on file length
        int num_chunks = file_length / NUM_WORDS_PER_CHUNK;
        if (file_length % NUM_WORDS_PER_CHUNK != 0){
            num_chunks++;
        }
        // write chunks to files
        for (int i = 0; i < num_chunks; i++){
            char* chunk_file_path = malloc(sizeof(char) * 100);
            sprintf(chunk_file_path, "%s_%d", file_path, i);
            FILE* chunk_fp = fopen(chunk_file_path, "w");
            if (chunk_fp == NULL) {
                printf("Error opening file %s", chunk_file_path);
                return 1;
            }
            int chunk_length = NUM_WORDS_PER_CHUNK;
            if (i == num_chunks - 1){
                chunk_length = file_length % NUM_WORDS_PER_CHUNK;
            }
            for (int j = 0; j < chunk_length; j++){
                fprintf(chunk_fp, "%s\n", word_arr[i * NUM_WORDS_PER_CHUNK + j]);
            }
            fclose(chunk_fp);
            free(chunk_file_path);
        }
        // free allocated memory for each string in word_arr
        for (int i = 0; i < file_length; i++) {
            free(word_arr[i]);
        }
        free(word_arr);
        return 0;
    }
}