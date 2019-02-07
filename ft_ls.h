
#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft/libft.h"
#include <sys/ioctl.h>

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
	t_flags *flags;
	char *path;
}					t_props;

typedef struct		s_folder_content
{
	DIR		*dir;
	char	*file_name;
}					t_folder_content;

#endif
