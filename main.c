
#include <sys/ioctl.h>
#include "ft_ls.h"

void ft_set_each(t_flags *flags, char n)
{
	flags->r_small = n;
	flags->a = n;
	flags->r_big = n;
	flags->l = n;
	flags->t = n;
	flags->noFlags = n;
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
	*(argv) = *(argv) + 1;
	while (*argv)
	{
		if (ft_strchr(*argv, '-'))
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
							 (char) 0 : (char) 255;
			return (flags);
		}
		*(argv) = *(argv) + 1;
	}
	flags->noFlags = 1;
	return (flags);
}


void get_t_size(int argc, char *const *argv)
{
	struct winsize w;
	t_props props;

	props.flags = scan_flags(argv, argc);
	props.flags->is_terminal = (char) (isatty(fileno(stdin)) ? 1 : 0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	props.win_size = w.ws_row;

}

int main(int argc, char **argv)
{
	get_t_size(argc, argv);

	return 0;
}
