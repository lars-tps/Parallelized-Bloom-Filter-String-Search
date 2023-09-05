////////////////////////////////////////////////////////////////////////////////////////////////
// bloom_filter.c
// ---------------------------------------------------------------------------------------------
// Author: Tan Pei Sheng
// Last modified: September 6th 2023
//////////////////////////////////////////////////////////////////////////////////////////////
#include "bloom_filter.h"

static int _hash(char* str, int bit_arr_size, int k);
/*
 * Function:  _APHash
 * --------------------
 * Hash function used for hashing SHA-256 output.
 * Sourced from: https://www.programmingalgorithms.com/algorithm/ap-hash/c/, accessed on September 6th 2023
 *
 * str: string to hash
 * length: length of string
 * 
 * returns: hash value
 */
unsigned int _APHash(char* str, unsigned int length);

bool* bloom_filter_create_bit_array(bool* bit_arr_ptr, int bit_arr_size){
    for(int i = 0; i < bit_arr_size; i++){
        bit_arr_ptr[i] = false;
    }
    return bit_arr_ptr;
}

void bloom_filter_insert(bool* bit_arr_ptr, int bit_arr_size, char* str){
    
    if (!bloom_filter_search(bit_arr_ptr, bit_arr_size, str)){
        // Number of hashing function is based on 1,376,656 words of input, 5% false positive rate, and bit array size of 8,583,759
        int a = _hash(str, bit_arr_size, 1);
        int b = _hash(str, bit_arr_size, 2);
        int c = _hash(str, bit_arr_size, 3);
        int d = _hash(str, bit_arr_size, 4);
        int e = _hash(str, bit_arr_size, 5);

        bit_arr_ptr[a] = true;
        bit_arr_ptr[b] = true;
        bit_arr_ptr[c] = true;
        bit_arr_ptr[d] = true;
        bit_arr_ptr[e] = true;
    }
}

bool bloom_filter_search(bool* bit_arr_ptr, int bit_arr_size, char* str){
    int a = _hash(str, bit_arr_size, 1);
    int b = _hash(str, bit_arr_size, 2);
    int c = _hash(str, bit_arr_size, 3);
    int d = _hash(str, bit_arr_size, 4);
    int e = _hash(str, bit_arr_size, 5);

    if (bit_arr_ptr[a] && bit_arr_ptr[b] && bit_arr_ptr[c] && bit_arr_ptr[d] && bit_arr_ptr[e]){
        return true;
    }
    return false;
}

int test_hash(bool* bit_arr_ptr, int bit_arr_size, char* str, int k){
    return _hash(str, bit_arr_size, k);
}

static int _hash(char* str, int bit_arr_size, int k){
    int hash = 0;
    int str_length = strlen(str);
    // Convert string to sha256 hash
    uint8_t temp_hash_1[32];
    calc_sha_256(temp_hash_1, str, str_length);
    // Chaining sha256 k-1 times
    for (int i = 0; i < k-1; i++) {
        uint8_t temp_hash_2[32];
        calc_sha_256(temp_hash_2, temp_hash_1, 32);
        memcpy(temp_hash_1, temp_hash_2, 32); // replace temp_hash_1 with temp_hash_2
    }
    // For every character in sha256 hash, cast to int and add to hash. After the addition, modulo hash by bit_arr_size.
    hash = _APHash((char*)temp_hash_1, 32) % bit_arr_size;
    
    return hash;
}

unsigned int _APHash(char* str, unsigned int length) {
	unsigned int hash = 0xAAAAAAAA;
	unsigned int i = 0;

	for (i = 0; i < length; str++, i++)
	{
		hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
			(~((hash << 11) + ((*str) ^ (hash >> 5))));
	}

	return hash;
}