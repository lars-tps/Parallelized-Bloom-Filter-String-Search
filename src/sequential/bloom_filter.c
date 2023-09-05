#include "bloom_filter.h"

bool * bloom_filter_create_bit_array(bool * bit_arr_ptr, int bit_arr_size){
    bit_arr_ptr = malloc(bit_arr_size * sizeof(bool));
    for(int i = 0; i < bit_arr_size; i++){
        bit_arr_ptr[i] = false;
    }
    return bit_arr_ptr;
}

void bloom_filter_insert(int* bit_arr_ptr, int bit_arr_size, char* str){

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