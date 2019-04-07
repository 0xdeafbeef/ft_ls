/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_long_format_additional.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:02:50 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/07 18:02:52 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	majors_and_size_parse(struct stat *structstat,
		t_files_attrib *atr)
{
	if (S_ISCHR((*structstat).st_mode))
	{
		atr->major = major((*structstat).st_rdev);
		atr->minor = minor((*structstat).st_rdev);
	}
	else
		atr->block_size = (*structstat).st_blocks;
}

void	link_parse(size_t len, t_files_attrib *atr)
{
	atr->st_mode_to_char[0] = 'l';
	atr->link_pointer = ft_strnew(len);
	errno = 0;
	readlink(atr->full_path, atr->link_pointer, len);
	if (errno)
		print_error(atr->full_path, errno, atr);
	atr->link_pointer[len - 1] = 0;
}
