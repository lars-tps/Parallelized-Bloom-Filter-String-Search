#include "./word_counter.h"

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
bool is_word_in_array(char* word, char** arr, int arr_size);

bool is_word_in_array(char* word, char** arr, int arr_size){
    for (int i = 0; i < arr_size; i++) {
        if (strcmp(word, arr[i]) == 0) { //strcmp returns 0 if strings are equal
            return true;
        }
    }
    return false;
}

int word_counter_total_word_counter(char* file_path){
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file %s", file_path);
        return 1;
    }

    char str[100];
    int total_word_count = 0;
    while (fscanf(fp, "%s\n", str) != EOF) {
        total_word_count++;
    }
    fclose(fp);
    return total_word_count;
}

int word_counter_total_unique_word_counter(char* file_path){
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file %s", file_path);
        return 1;
    }

    char str[100];
    int total_unique_word_count = 0;
    char** unique_words_arr = malloc(sizeof(char*) * word_counter_total_word_counter(file_path));
    int unique_words_arr_size = 0;
    // add unique words to unique_words_arr and increment counters if word is not in unique_words_arr
    while (fscanf(fp, "%s\n", str) != EOF) {
        if (_is_word_in_array(str, unique_words_arr, unique_words_arr_size) == 0) { // if word is not in array
            unique_words_arr[unique_words_arr_size] = strdup(str);
            unique_words_arr_size++;
            total_unique_word_count++;
        }
    }

    // output unique_wordlist to txt file
    FILE* wordlist_fp = fopen("unique_wordlist.txt", "w");
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

    return total_unique_word_count;
}