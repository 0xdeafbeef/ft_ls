
#include "ft_ls.h"

void ft_set_each(t_flags *flags, char n)
{
	flags->r_small = n;
	flags->a = n;
	flags->r_big = n;
	flags->l = n;
	flags->t = n;
	flags->noFlags = n;
	flags->is_terminal=n;
}

t_flags *scan_flags(char **argv, int argc)
{
	t_flags *flags;

	flags = malloc(sizeof(t_flags));
	ft_set_each(flags, 0);
	if (argc < 2)
	{
		flags->noFlags = 1;
		return (flags);
	}
	*(argv)++;
	while (*argv)
	{
		if (*argv[0]=='-')
		{
			if (ft_strchr(*argv, 'R'))
				flags->r_big = 1;
			if (ft_strchr(*argv, 'a'))
				flags->a = 1;
			if (ft_strchr(*argv, 'r'))
				flags->r_small = 1;
			if (ft_strchr(*argv, 't'))
				flags->t = 1;
			if (ft_strchr(*argv, 'l'))
				flags->l = 1;
			flags->noFlags = (ft_strchr(*argv, 'R') || ft_strchr(*argv, 'a') ||
							  ft_strchr(*argv, 'r') || ft_strchr(*argv, 't') ||
							  ft_strchr(*argv, 'l')) ?
							 (char) 0 : (char) 1;
		}
		*(argv) ++;
	}
	if (flags->noFlags)
		return (flags);
	return (flags);
}


t_props get_t_size_and_flags(int argc, char **argv)
{
	struct winsize w;
	t_props props;

	props.flags = scan_flags(argv, argc);
	props.flags->is_terminal = (char) (isatty(fileno(stdin)) ? 1 : 0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	props.win_size = w.ws_row;
	return (props);
}

int main(int argc, char **argv)
{
	t_props props;
	props = get_t_size_and_flags(argc, argv);

	return 0;
}

void read_without_a_flag(char *path)
{
	t_files_list *files_list;
	DIR *dir;
	struct dirent *direntp;
	dir = opendir(path);

	while (direntp=readdir(dir))
	{
		
	}
	files_list = malloc(sizeof(t_files_list));
}
