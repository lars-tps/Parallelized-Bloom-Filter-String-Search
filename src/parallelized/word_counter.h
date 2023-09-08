////////////////////////////////////////////////////////////////////////////////////////////////
// word_counter.h
// ---------------------------------------------------------------------------------------------
// Author: Tan Pei Sheng
// Last modified: September 8th 2023
//////////////////////////////////////////////////////////////////////////////////////////////
#ifndef WORD_COUNTER_H 
#define WORD_COUNTER_H 

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

/*
 * Function:  word_counter_total_word_counter
 * --------------------
 * Counts the total number of words in a file
 *
 *  file_path: path to file
 * 
 *  returns: total number of words in file
 */
int word_counter_total_word_counter(char* file_path);

/*
 * Function:  word_counter_total_unique_word_counter
 * --------------------
 * Counts the total number of unique words in a file
 *
 *  file_path: path to file
 * 
 *  returns: total number of unique words in file
 */
int word_counter_total_unique_word_counter(char* file_path);

/*
 * Function:  calc_file_length
 * --------------------
 * Calculates the length of a file
 *
 *  file_path: path to file
 * 
 *  returns: length of file
 */
int calc_file_length(char* file_path);

#endif