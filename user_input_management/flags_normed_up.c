/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_normed_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 23:43:16 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/08 23:44:15 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	assign_all(t_props **props, t_path **pat, t_path **p_handler,
		t_bool *is_first_asign)
{
	(*p_handler) = NULL;
	(*is_first_asign) = true;
	(*pat) = NULL;
	(*props) = ft_memalloc(sizeof(t_props));
}
