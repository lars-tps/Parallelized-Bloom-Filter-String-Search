////////////////////////////////////////////////////////////////////////////////////////////////
// main.c
// ---------------------------------------------------------------------------------------------
// Author: Tan Pei Sheng
// Last modified: September 6th 2023
//////////////////////////////////////////////////////////////////////////////////////////////
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "./bloom_filter.h"
#define BIT_ARR_SIZE 8583759

int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Please provide at least one text file for insertions and one query file for searches.");
        return 1;
    } else if (argc < 3) {
        printf("Please provide a query file for searches.");
    } else {
        // Create bloom filter
        bool* bit_arr_ptr = malloc(BIT_ARR_SIZE * sizeof(bool));
        bloom_filter_create_bit_array(bit_arr_ptr, BIT_ARR_SIZE);

        // Insert words from text files into bloom filter
        for (int i = 1; i < argc - 1; i++) { // every file except the last one
            FILE* fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("Error opening file %s", argv[i]);
                return 1;
            }
            char str[100]; 
            while (fscanf(fp, "%s\n", str) != EOF) {
                bloom_filter_insert(bit_arr_ptr, BIT_ARR_SIZE, str);
            }
            fclose(fp);
        }

        // Search for words from query file in bloom filter
        FILE* fp = fopen(argv[argc - 1], "r"); // the last file is the query file
        FILE* result_fp = fopen("result.txt", "w");
        int accurate_word_count = 0;
        int total_word_count = 0;
        if (fp == NULL) {
            printf("Error opening file %s", argv[argc - 1]);
            return 1;
        }
        char str[100]; 
        int tag;
        while (fscanf(fp, "%s %d\n", str, &tag) != EOF) {
            total_word_count++;
            if (bloom_filter_search(bit_arr_ptr, BIT_ARR_SIZE, str)) {
                fprintf(result_fp, "%s 1\n", str);
                if (tag == 1) {
                    accurate_word_count++;
                }
            } else {
                fprintf(result_fp, "%s 0\n", str);
                if (tag == 0) {
                    accurate_word_count++;
                }
            }
        }
        float accuracy = (float)accurate_word_count / (float)total_word_count * 100;
        printf("Bloom Filter Accuracy: %.2f%%\n", accuracy);
        free(bit_arr_ptr);
        fclose(result_fp);
        fclose(fp);
    }
}