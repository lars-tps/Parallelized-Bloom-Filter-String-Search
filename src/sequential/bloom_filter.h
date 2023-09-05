#include <stdbool.h>
#include <string.h>

/*
 * Function:  bloom_filter_create_bit_array
 * --------------------
 * Creates an array of boolean bits of size bit_arr_size
 *
 *  bit_arr_ptr: pointer to array
 *  bit_arr_size: size of array
 * 
 *  returns: An array of boolean bits of size bit_arr_size
 */
bool * bloom_filter_create_bit_array(bool * bit_arr_ptr, int bit_arr_size);

/*
 * Function:  bloom_filter_insert
 * --------------------
 * Inserts a string into the bloom filter bit array
 *
 *  bit_arr_ptr: pointer to array
 *  bit_arr_size: size of array
 *  str: string to insert
 */
void bloom_filter_insert(int* bit_arr_ptr, int bit_arr_size, char* str);

/*
 * Function:  bloom_filter_search
 * --------------------
 * Searches for a string in the bloom filter bit array
 *
 *  bit_arr_ptr: pointer to array
 *  bit_arr_size: size of array
 *  str: string to search for
 *
 *  returns: true if string is found, false otherwise
 */
bool bloom_filter_search(int* bit_arr_ptr, int bit_arr_size, char* str);