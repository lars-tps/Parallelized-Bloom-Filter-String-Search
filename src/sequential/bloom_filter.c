////////////////////////////////////////////////////////////////////////////////////////////////
// bloom_filter.c
// ---------------------------------------------------------------------------------------------
// Author: Tan Pei Sheng
// Last modified: September 6th 2023
//////////////////////////////////////////////////////////////////////////////////////////////
#include "bloom_filter.h"

static int _hash(char* str, int bit_arr_size, int k);

bool* bloom_filter_create_bit_array(bool* bit_arr_ptr, int bit_arr_size){
    for(int i = 0; i < bit_arr_size; i++){
        bit_arr_ptr[i] = false;
    }
    return bit_arr_ptr;
}

void bloom_filter_insert(bool* bit_arr_ptr, int bit_arr_size, int num_hash_functions, char* str){
    if (!bloom_filter_search(bit_arr_ptr, bit_arr_size, num_hash_functions, str)){
        for (int k = 1; k <= num_hash_functions; k++){
            int hash = _hash(str, bit_arr_size, k);
            bit_arr_ptr[hash] = true;
        }
    }
}

bool bloom_filter_search(bool* bit_arr_ptr, int bit_arr_size, int num_hash_functions, char* str){
    bool flag = true;
    for (int k = 1; k <= num_hash_functions; k++){
        int hash = _hash(str, bit_arr_size, k);
        if (bit_arr_ptr[hash] == false){
            flag = false;
        }
    }
    return flag;
}

int test_hash(bool* bit_arr_ptr, int bit_arr_size, char* str, int k){
    return _hash(str, bit_arr_size, k);
}

static int _hash(char* str, int bit_arr_size, int k) {
    int hash = 0;
    int str_length = strlen(str);

    for (int i = 0; i < k; i++){
        for (int j = 0; j < str_length; j++){
            hash = (hash + (int)str[j] * (int)str[str_length-j-1]) + bit_arr_size/k;
        }
        hash = hash % bit_arr_size;
    }
    
    return hash;
}