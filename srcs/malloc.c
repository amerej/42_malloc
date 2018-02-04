/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/04 16:39:36 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
** TYPEOF(t_map) defined in malloc.h as an extern variable
** 3 types_tab elems : one for TINY / SMALL / LARGE
** each types_tab elem contains a list of mmap results (t_block)
*/

size_t	get_alloc_pages_count()
{
	int		type;
	t_map	*map;
	size_t	count;

	type = 0;
	count = 0;
	while (type < MAX_TYPE)
	{
		if ((map = g_types_tab[type])) {
			while (map)
			{
				count += map->page_count;
				map = map->next;
			}
		}
		type++;
	}
	return (count);
}

t_map	*g_types_tab[MAX_TYPE] = {NULL, NULL, NULL};

void	*malloc(size_t size)
{
	t_map 			*map_lst;
	t_block			*block;
	int				type;
	struct rlimit	rt;

	ft_putstr("\nf(MALLOC), ptr"); ft_putnbr_base((long)size, 10); 

	if (!size || getrlimit(RLIMIT_AS, &rt) || rt.rlim_max < size)
		return (NULL);

	type = get_type(size);
	size = get_size(size);
	
	if (!(map_lst = get_map_lst(type, size))) // get the right map type to work on
		return (NULL);

	if (!(block = get_block(map_lst, type, size)))
		return (NULL);

	// show_alloc_mem();

	ft_putstr("\nmalloc return -- &block->ptr: ");
	ft_putnbr_base((long)block->ptr, 16);
	ft_putstr("\n");

	return (block->ptr);
}