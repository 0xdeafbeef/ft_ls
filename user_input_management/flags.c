/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:11:27 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/28 16:14:49 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

void find_flag_pattern(char **argv, t_props *props)
{
	if (ft_strchr(*argv, 'R'))
		props->flag |= R_BIG;
	if (ft_strchr(*argv, 'a'))
		props->flag |= A;
	if (ft_strchr(*argv, 'r'))
		props->flag |= R_SMALL;
	if (ft_strchr(*argv, 't'))
		props->flag |= T;
	if (ft_strchr(*argv, 'l'))
		props->flag |= L;
}

t_props *scan_flags_path(char **argv, int argc)
{
	t_props *props;
	t_path *pat;
	t_path *p_handler;
	t_bool is_first_asign;

	p_handler = NULL;
	is_first_asign = true;
	pat = NULL;
	props = ft_memalloc(sizeof(t_props));

	if (argc < 2)
	{
		props->path = ft_path_append_horizontal(pat, ".");
		return (props);
	}
	++(argv);
	while (*argv)
	{
		if (*argv[0] == '-')
			find_flag_pattern(argv, props);
		else
		{
			pat = ft_path_append_horizontal(pat, *argv);
			if (is_first_asign)
				p_handler = pat;
			is_first_asign = false;
		}
		++(argv);
	}
	props->path = p_handler;
	if (!props->path)
		props->path = ft_path_append_horizontal(pat, ".");
	return (props);
}


t_props *get_t_size_and_flags(int argc, char **argv)
{
	struct winsize w;
	t_props *props;

	props = scan_flags_path(argv, argc);
	sort_path(props->path);
	props->isterm =  (isatty(fileno(stdout)) ? 1 : 0);
	if(props->isterm)
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		props->win_size = w.ws_col;
	}
	return (props);
}