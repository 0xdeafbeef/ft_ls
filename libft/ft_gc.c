/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:10:50 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/11 15:19:14 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gc_vector	*init_tgc_vector(ssize_t ssize)
{
	t_gc_vector *vector;

	vector = malloc(sizeof(t_gc_vector));
	ft_bzero(vector, sizeof(t_gc_vector));
	if (vector)
	{
		vector->len = TGC_OPTIMAL_SIZE;
		vector->size = ssize;
		vector->data = malloc(ssize * TGC_OPTIMAL_SIZE);
	}
	return (vector);
}

void		ft_gc(t_gc_vector **vector)
{
	size_t size;

	if (*vector)
	{
		size = (*vector)->count;
		while (size--)
		{
			free((*vector)->data[size]);
		}
		free((*vector)->data);
		free(*vector);
	}
}

void		ft_resize_vector(t_gc_vector **vector)
{
	void **temp;
	void **vec_data;

	if (*vector)
	{
		temp = (*vector)->data;
		vec_data = malloc(((*vector)->len * (*vector)->size) * 2);
		vec_data = ft_memmove(vec_data, temp, (*vector)->len * (*vector)->size);
		free(temp);
		(*vector)->data = vec_data;
		(*vector)->len = (*vector)->len * 2;
	}
}

void		ft_tgc_append(t_gc_vector **vector, void **data)
{
	if (*vector)
	{
		if ((*vector)->len - (*vector)->count <= 1)
			ft_resize_vector(vector);
		(*vector)->data[(*vector)->count] = data;
		++(*vector)->count;
	}
}
