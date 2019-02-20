/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:47:13 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/20 18:26:58 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void main_wrap(int argc, char **argv)
{
	t_props *props;

	props = get_t_size_and_flags(argc, argv);
	get_path_list(props);
	ft_list_sort_all(props);

	print_all(props->path->attrib);
}

int main(int argc, char **argv)
{
	main_wrap(argc, argv);
//	pat = props->path;
//	while (pat)
//	{
//		print_path_list(pat);
//		pat = pat->next;
//	}
	ft_gc(&g_memaloced);
	return 0;
}