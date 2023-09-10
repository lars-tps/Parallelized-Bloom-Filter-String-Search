#include "./word_counter.h"

#define NUM_THREADS 8 // number of threads to use for parallelization, adjust accordingly to CPU core count

/*
 * Function:  _is_word_in_array
 * --------------------
 * Checks if a word is in an array of words
 *
 *  word: word to check
 *  arr: array of words
 *  arr_size: size of array
 * 
 *  returns: true if word is in array, false otherwise
 */
bool _is_word_in_array(char* word, char** arr, int arr_size);


bool _is_word_in_array(char* word, char** arr, int arr_size){
    for (int i = 0; i < arr_size; i++) {
        if (strcmp(word, arr[i]) == 0) { //strcmp returns 0 if strings are equal
            return true;
        }
    }
    return false;
}

int word_counter_total_unique_word_counter(char* file_path, int file_length){
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file %s", file_path);
        return 1;
    }

    // create array of unique words
    char str[100];
    char** unique_words_arr = malloc(sizeof(char*) * file_length);
    int unique_words_arr_size = 0;
    // count total number of unique words in file, in parallel
    #pragma omp parallel for private(str) shared(unique_words_arr, unique_words_arr_size) schedule(dynamic)
    for (int i = 0; i < file_length; i++) {
        fscanf(fp, "%s\n", str);
        if (!_is_word_in_array(str, unique_words_arr, unique_words_arr_size)) 
        #pragma omp critical
        {
            unique_words_arr[unique_words_arr_size] = strdup(str);
            unique_words_arr_size++;
        }
    }

    // output unique_wordlist to txt file
    FILE* wordlist_fp = fopen("unique_wordlist.txt", "a");
    #pragma omp parallel for
    for (int i = 0; i < unique_words_arr_size; i++) {
        fprintf(wordlist_fp, "%s\n", unique_words_arr[i]);
    }
    fclose(wordlist_fp);

    // free allocated memory for each string in unique_words_arr
    for (int i = 0; i < unique_words_arr_size; i++) {
        free(unique_words_arr[i]);
    }

    free(unique_words_arr);
    fclose(fp);

    return unique_words_arr_size;
}

int calc_file_length(char* file_path){
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file %s", file_path);
        return 1;
    }

    int file_length = 0;
    char str[100];
    while (fscanf(fp, "%s\n", str) != EOF) {
        file_length++;
    }
    fclose(fp);
    return file_length;
}