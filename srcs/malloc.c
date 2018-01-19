/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/07 13:23:00 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
** TYPEOF(t_map) defined in malloc.h as an extern variable
** 3 types_tab elems : one for TINY / SMALL / LARGE
** each types_tab elem contains a list of mmap results (t_block)
*/

t_map	*g_types_tab[MAX_TYPE] = {NULL, NULL, NULL};

void	*malloc(size_t size)
{
	t_map 	*map_lst;
	t_block	*block;
	int		type;

	ft_putstr("\nf(MAIN)");

	if (size <= 0)
		return (NULL); // check expected return	

	type = get_type(size);
	size = get_size(size);
	
	map_lst = get_map_lst(type, size); // get the right map type to work on
	if (!map_lst)
		return (NULL);

	block = get_block(map_lst, type, size);

	ft_putstr("\nmalloc return -- &block->ptr: ");
	ft_putnbr_base((long)block->ptr, 16);
	ft_putstr("\n");
	
	return (block->ptr);
}