//
// Created by odm3n on 10.03.19.
//

#ifndef FT_LS_STRUCTURES_H
#define FT_LS_STRUCTURES_H

#include "stdlib.h"

typedef struct s_print
{
	unsigned short int links_max;
	unsigned int owner_len_max;
	unsigned int group_name_max;
	unsigned long int tmp;
	unsigned int nodes_count;
	unsigned int filename_max;
	unsigned int file_size_max;
	unsigned int pointers_len;
	char *ptr;
} 				t_print;
#endif //FT_LS_STRUCTURES_H
