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
        FILE* fp = fopen(argv[argc - 1], "r"); // the last file
        if (fp == NULL) {
            printf("Error opening file %s", argv[argc - 1]);
            return 1;
        }
        char str[100]; 
        int tag;
        while (fscanf(fp, "%s %d\n", str, &tag) != EOF) {
            if (bloom_filter_search(bit_arr_ptr, BIT_ARR_SIZE, str)) {
                int test_hash_val_1 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 1);
                int test_hash_val_2 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 2);
                int test_hash_val_3 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 3);
                int test_hash_val_4 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 4);
                int test_hash_val_5 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 5);
                printf("%s is probably in the bloom filter. \nhash_1 = %d\nhash_2 = %d\nhash_3 = %d\nhash_4 = %d\nhash_5 = %d\n", str, test_hash_val_1, test_hash_val_2, test_hash_val_3, test_hash_val_4, test_hash_val_5);
            } else {
                int test_hash_val_1 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 1);
                int test_hash_val_2 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 2);
                int test_hash_val_3 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 3);
                int test_hash_val_4 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 4);
                int test_hash_val_5 = test_hash(bit_arr_ptr, BIT_ARR_SIZE, str, 5);
                printf("%s is definitely not in the bloom filter. \nhash_1 = %d\nhash_2 = %d\nhash_3 = %d\nhash_4 = %d\nhash_5 = %d\n", str, test_hash_val_1, test_hash_val_2, test_hash_val_3, test_hash_val_4, test_hash_val_5);
            }
        }
        free(bit_arr_ptr);
        fclose(fp);
    }
}