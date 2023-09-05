#include "bloom_filter.h"

bool * bloom_filter_create_bit_array(bool * bit_arr_ptr, int bit_arr_size){
    bit_arr_ptr = malloc(bit_arr_size * sizeof(bool));
    for(int i = 0; i < bit_arr_size; i++){
        bit_arr_ptr[i] = false;
    }
    return bit_arr_ptr;
}

void bloom_filter_insert(int* bit_arr_ptr, int bit_arr_size, char* str){
    
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

bool bloom_filter_search(int* bit_arr_ptr, int bit_arr_size, char* str){
    return false;
}

static int _hash1(char* str, int bit_arr_size){
    return 0;
}

static int _hash2(char* str, int bit_arr_size){
    return 0;
}

static int _hash3(char* str, int bit_arr_size){
    return 0;
}

static int _hash4(char* str, int bit_arr_size){
    return 0;
}

static int _hash5(char* str, int bit_arr_size){
    return 0;
}