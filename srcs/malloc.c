/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 14:52:11 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** TYPEOF(t_map) defined in malloc.h as an extern variable
** 3 types_tab elems : one for TINY / SMALL / LARGE
** each types_tab elem contains a list of mmap results (t_block)
*/

size_t	get_alloc_pages_count(void)
{
	int		type;
	t_map	*map;
	size_t	count;

	type = 0;
	count = 0;
	while (type < MAX_TYPE)
	{
		if ((map = g_types_tab[type]))
		{
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

void	*ts_malloc(size_t size)
{
	t_map			*map_lst;
	t_block			*block;
	int				type;
	struct rlimit	rt;

	if (!size || getrlimit(RLIMIT_AS, &rt) || rt.rlim_max < size)
		return (NULL);
	size = get_size(size);
	type = get_type(size);
	if (!(map_lst = get_map_lst(type, size)))
		return (NULL);
	if (!(block = get_block(map_lst, type, size)))
		return (NULL);
	return (block->ptr);
}
