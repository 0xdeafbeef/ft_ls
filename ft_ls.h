
#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft/libft.h"

typedef struct		s_flags
{
	char noFlags;
	char l;
	char r_big;
	char a;
	char r_small;
	char t;
	char is_terminal;
}					t_flags;

typedef struct		s_props
{
	int win_size;
	t_flags flags;
}		t_props;
#endif
