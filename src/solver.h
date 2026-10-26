#ifndef SOLVER_H
#define SOLVER_H

#include <stddef.h>

#define MAX_WORDS 8      
#define MAX_WORD_LEN 16  
#define UNIQ_LET 10
#define LET_IN_ALF 26


int solve_puzzle(const char *input, char *out, size_t out_size);

#endif