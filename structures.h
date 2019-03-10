//
// Created by odm3n on 10.03.19.
//

#ifndef FT_LS_STRUCTURES_H
#define FT_LS_STRUCTURES_H

#include "stdlib.h"

typedef struct s_print
{
	unsigned short int links_max;
	int owner_len_max;
	int group_name_max;
	unsigned int tmp;
	size_t write_size;
	int verical_len;
	int max_name_len;
	int entry_size;
	char *result;
} 				t_print;
#endif //FT_LS_STRUCTURES_H
