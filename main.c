/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:47:13 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/09 21:44:59 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_props *props;
	t_path *pat;
//
//	props = get_t_size_and_flags(argc, argv);
//	get_path_list(props);

	t_files_attrib *attrib;
	char *p;

	p = ft_strdup(".");
	//printf("%ld", sizeof( t_files_attrib ));
	//free(attrib);
	attrib = create_tatr(p);

	ft_open_folder(p, attrib);
//	pat = props->path;
//	while (pat)
//	{
//		print_path_list(pat);
//		pat = pat->next;
//	}

	return 0;
}