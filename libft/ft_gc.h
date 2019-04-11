/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:08:59 by qhetting          #+#    #+#             */
/*   Updated: 2019/03/14 14:10:24 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_FT_GC_H
#include <stdio.h>

#include <stdlib.h>
#define GC_FT_GC_H
#define TGC_OPTIMAL_SIZE (2u<<5u)
typedef struct s_gc_vector
{
	ssize_t count;
	ssize_t len;
	ssize_t size;
	void **data;
}				t_gc_vector;
void ft_gc(t_gc_vector **vector);
void ft_tgc_append(t_gc_vector **vector,void **d);
t_gc_vector *init_tgc_vector(ssize_t ssize);
extern t_gc_vector *g_memaloced;
#endif