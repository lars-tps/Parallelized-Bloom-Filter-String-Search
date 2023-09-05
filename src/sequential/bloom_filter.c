#include "bloom_filter.h"

static int _hash1(char* str, int bit_arr_size);
static int _hash2(char* str, int bit_arr_size);
static int _hash3(char* str, int bit_arr_size);
static int _hash4(char* str, int bit_arr_size);
static int _hash5(char* str, int bit_arr_size);

bool* bloom_filter_create_bit_array(bool* bit_arr_ptr, int bit_arr_size){
    for(int i = 0; i < bit_arr_size; i++){
        bit_arr_ptr[i] = false;
    }
    return bit_arr_ptr;
}

void bloom_filter_insert(bool* bit_arr_ptr, int bit_arr_size, char* str){
    
    if (!bloom_filter_search(bit_arr_ptr, bit_arr_size, str)){
        // Number of hashing function is based on 1,376,656 words of input, 5% false positive rate, and bit array size of 8,583,759
        int a = _hash1(str, bit_arr_size);
        int b = _hash2(str, bit_arr_size);
        int c = _hash3(str, bit_arr_size);
        int d = _hash4(str, bit_arr_size);
        int e = _hash5(str, bit_arr_size);

        bit_arr_ptr[a] = true;
        bit_arr_ptr[b] = true;
        bit_arr_ptr[c] = true;
        bit_arr_ptr[d] = true;
        bit_arr_ptr[e] = true;
    }
}

bool bloom_filter_search(bool* bit_arr_ptr, int bit_arr_size, char* str){
    int a = _hash1(str, bit_arr_size);
    int b = _hash2(str, bit_arr_size);
    int c = _hash3(str, bit_arr_size);
    int d = _hash4(str, bit_arr_size);
    int e = _hash5(str, bit_arr_size);

    if (bit_arr_ptr[a] && bit_arr_ptr[b] && bit_arr_ptr[c] && bit_arr_ptr[d] && bit_arr_ptr[e]){
        return true;
    }
    return false;
}

static int _hash1(char* str, int bit_arr_size){
    // _hash1 idea sourced from: https://www.geeksforgeeks.org/bloom-filters-introduction-and-python-implementation/
    int hash = 0;
    int str_length = strlen(str);
    // for every character, cast it to int and add to hash, then modulo hash by bit_arr_size.
    for (int i = 0; i < str_length; i++) 
    {
        hash = (hash + ((int)str[i]));
        hash = hash % bit_arr_size;
    }
    return hash;
}

static int _hash2(char* str, int bit_arr_size){
    int hash = 0;
    int str_length = strlen(str);
    // for every character, cast to int multiply by 2-squared and add to hash, after getting sum modulo hash by bit_arr_size.
    for (int i = 0; i < str_length; i++) 
    {
        hash = (hash + ((int)str[i]) * 2 * 2);
        hash = hash % bit_arr_size;
    }
    return hash;
}

static int _hash3(char* str, int bit_arr_size){
    int hash = 0;
    int str_length = strlen(str);
    for(int i = 0; i < str_length; i++){
        hash = (hash + ((int)str[i]) * 3 * 3 * 3);
        hash = hash % bit_arr_size;
    }
    return hash;
}

static int _hash4(char* str, int bit_arr_size){
    int hash = 0;
    int str_length = strlen(str);
    for(int i = 0; i < str_length; i++){
        hash = (hash + ((int)str[i]) * 4 * 4 * 4 * 4);
        hash = hash % bit_arr_size;
    }
    return hash;
}

static int _hash5(char* str, int bit_arr_size){
    int hash = 0;
    int str_length = strlen(str);
    for(int i = 0; i < str_length; i++){
        hash = (hash + ((int)str[i]) * 5 * 5 * 5 * 5 * 5);
        hash = hash % bit_arr_size;
    }
    return hash;
}