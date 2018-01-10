	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/07 03:06:16 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		update_map(t_block *block)
{
	if (block->next && block->next->free == TRUE)
		block->next = block->next->next;
	if (block->prev && block->prev->free == TRUE)
	{
		block->prev->size = block->prev->size + block->size + BLOCK_SIZE;
 		block->prev->next = block->next;
	}
}

static void		browse_map(t_map *map, t_block *to_free, t_map *prev_map, )
{
	t_bool	to_unmap;

	to_unmap = TRUE;
	while (block)
	{
		if (block == to_free)
		{
			map->free_space = map->free->space + BLOCK_SIZE;
			update_map(block);
		}
		else if (block->free == FALSE)
			to_unmap = FALSE;
		block = block->next;
	}

	if (to_unmap == TRUE)
	{
		munmap(map, sizeof(map));
		(map_prev) ? map_prev->next = map->next : map = map->next;
	}
}

void    free(void *ptr)
{
	t_block     *block;
	t_map		*map;
	t_map		*prev_map;
	int			types;

	types = 0;
	prev_map = NULL;
	while (map = g_types_tab[types++])
	{
		while (map)
		{
			if (map == (ptr & 0xFFFFFF000))
			{
				browse_map(map, (void*)ptr - BLOCK_SIZE, prev_map);
				return;
			}
			prev_map = map;
			map = map->next;
		}
	}
}