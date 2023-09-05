#include "./bloom_filter.h"
#include <stdio.h>
#define BIT_ARR_SIZE 8583759

int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Please provide at least one text file for insertions and one query file for searches.");
        return 1;
    } else if (argc < 3) {
        printf("Please provide a query file for searches.");
    } else {
        // Create bloom filter
        bool* bit_arr_ptr = malloc(BIT_ARR_SIZE * sizeof(int));
        bloom_filter_create_bit_array(bit_arr_ptr, BIT_ARR_SIZE);

        // Insert words from text files into bloom filter
        for (int i = 1; i < argc - 1; i++) { // every file except the last one
            FILE* fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("Error opening file %s", argv[i]);
                return 1;
            }
            char str[100];
            while (fscanf(fp, "%s", str) != EOF) {
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
        while (fscanf(fp, "%s", str) != EOF) {
            if (bloom_filter_search(bit_arr_ptr, BIT_ARR_SIZE, str)) {
                printf("%s is probably in the bloom filter.\n", str);
            } else {
                printf("%s is definitely not in the bloom filter.\n", str);
            }
        }
        free(bit_arr_ptr);
        fclose(fp);
    }
}