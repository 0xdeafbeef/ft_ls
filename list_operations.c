/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:50 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/28 16:59:45 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

t_files_attrib *create_atr(char *name)
{
	t_files_attrib *attrib;

	attrib = ft_memalloc(sizeof(t_files_attrib));
	if (name)
		attrib->filename = ft_strdup(name);
	return (attrib);
}
