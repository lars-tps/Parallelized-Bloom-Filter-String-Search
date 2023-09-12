////////////////////////////////////////////////////////////////////////////////////////////////
// main.c
// ---------------------------------------------------------------------------------------------
// Author: Tan Pei Sheng
// Last modified: September 8th 2023
//////////////////////////////////////////////////////////////////////////////////////////////
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "./bloom_filter.h"
#include "./word_counter.h"


int _calc_bit_array_size(int total_unique_word_count);
int _calc_num_hash_functions(int bit_arr_size, int total_unique_word_count);

int _calc_bit_array_size(int total_unique_word_count){
    // formula from Ian Boyd: https://stackoverflow.com/questions/658439/how-many-hash-functions-does-my-bloom-filter-need
    // accessed on 7th September 2023
    return -total_unique_word_count * log(0.01) / (log(2) * log(2));
}

int _calc_num_hash_functions(int bit_arr_size, int total_unique_word_count){
    // formula from Ian Boyd: https://stackoverflow.com/questions/658439/how-many-hash-functions-does-my-bloom-filter-need
    // accessed on 7th September 2023
    return bit_arr_size / total_unique_word_count * log(2); 
}

int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Please provide at least one text file for insertions and one query file for searches.");
        return 1;
    } else if (argc < 3) {
        printf("Please provide a query file for searches.");
    } else {

        // initialize time variables for timing the various parts of the program
        struct timespec start, end, startComp, endComp; 
	    double time_taken; 

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // UNIQUE WORD COUNTING
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        clock_gettime(CLOCK_MONOTONIC, &start); // start timer
        int total_unique_word_count = 0;
        int file_length = 0;
        for (int i = 1; i < argc - 1; i++) { // every file except the last one
            file_length = calc_file_length(argv[i]);
            total_unique_word_count += word_counter_total_unique_word_counter(argv[i], file_length);
        }

        clock_gettime(CLOCK_MONOTONIC, &end); // end timer
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
        printf("Total Unique Word Count Time: %lf\n", time_taken);

        printf("Total Unique Word Count from input text files: %d\n", total_unique_word_count);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // BLOOM FILTER CREATION
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        int bit_arr_size = _calc_bit_array_size(total_unique_word_count);
        printf("Bit Array Size: %d\n", bit_arr_size);
        int num_hash_functions = _calc_num_hash_functions(bit_arr_size, total_unique_word_count);
        printf("Number of Hash Functions: %d\n", num_hash_functions);

        // Create bloom filter
        bool* bit_arr_ptr = malloc(bit_arr_size * sizeof(bool));
        bloom_filter_create_bit_array(bit_arr_ptr, bit_arr_size);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // BLOOM FILTER INSERTION
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        clock_gettime(CLOCK_MONOTONIC, &start); // start timer

        for (int i = 1; i < argc - 1; i++) { // every file except the last one
            FILE* fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("Error opening file %s", argv[i]);
                return 1;
            }
            char str[100]; 
            int file_length = calc_file_length(argv[i]);
            #pragma omp parallel for private(str) num_threads(4)
            for (int j = 0; j < file_length; j++) {
                fscanf(fp, "%s\n", str);
                bloom_filter_insert(bit_arr_ptr, bit_arr_size, num_hash_functions, str);
            }

            fclose(fp);
        }

        clock_gettime(CLOCK_MONOTONIC, &end); // end timer
        time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
        printf("Bloom Filter Insertion Time: %lf\n", time_taken);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // BLOOM FILTER SEARCHING
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        FILE* fp = fopen(argv[argc - 1], "r"); // the last file is the query file
        FILE* result_fp = fopen("result.txt", "w");
        if (fp == NULL) {
            printf("Error opening file %s", argv[argc - 1]);
            return 1;
        }
        char str[100]; 
        int result_tag;
        int query_tag;

        clock_gettime(CLOCK_MONOTONIC, &startComp); // start timer

        file_length = calc_file_length(argv[argc - 1]);
        char** query_words_arr = malloc(sizeof(char*) * file_length);
        int* query_words_arr_result_tag = malloc(sizeof(int) * file_length);
        // Search for words from query file in bloom filter
        #pragma omp parallel for private(str, result_tag) num_threads(4)
        for (int i = 0; i < file_length; i++) {
            fscanf(fp, "%s %d\n", str, &query_tag);
            result_tag = bloom_filter_search(bit_arr_ptr, bit_arr_size, num_hash_functions, str);
            query_words_arr[i] = strdup(str);
            query_words_arr_result_tag[i] = result_tag;
        }

        clock_gettime(CLOCK_MONOTONIC, &endComp); // end timer
        // calculate and print time taken
        time_taken = (endComp.tv_sec - startComp.tv_sec) * 1e9;
        time_taken = (time_taken + (endComp.tv_nsec - startComp.tv_nsec)) * 1e-9;
        printf("Bloom Filter Search Time: %lf\n", time_taken);

        // output query_words_arr to txt file
        for (int i = 0; i < file_length; i++) {
            fprintf(result_fp, "%s %d\n", query_words_arr[i], query_words_arr_result_tag[i]);
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // CLEANUP
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        free(bit_arr_ptr);
        fclose(result_fp);
        fclose(fp);
    }
}