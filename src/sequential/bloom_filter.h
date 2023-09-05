#include <stdbool.h>

bool * bloom_filter_create_bit_array(bool * bit_arr_ptr, int bit_arr_size);
void bloom_filter_insert(int* bit_arr_ptr, int bit_arr_size, char* str);
bool bloom_filter_search(int* bit_arr_ptr, int bit_arr_size, char* str);