/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/11 19:40:10 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		update_map_blocks(t_block *block)
{
	if (block->free == TRUE && block->next && block->next->free == TRUE)
	{
		block->size += block->next->size + BLOCK_SIZE;
		block->next = block->next->next;
		if (block->next)
		{
			if (block->next->free == TRUE)
				return (update_map_blocks(block));
		}
		return (TRUE);
	}
	return (FALSE);
}

static void		mumnmap_and_update_maps(t_map **map, int maptype)
{
	size_t		map_full_size;
	t_map		*todel;

	todel = *map;
	map_full_size = todel->block->size + MAP_SIZE;
	(*map) = (*map)->next;
	if (*map)
		(*map)->prev = todel->prev;
	else if (todel->prev)
		todel->prev->next = NULL;
	if (!todel->next && todel->prev)
		g_types_tab[maptype]->last = todel->prev;
	else if (!todel->next && !todel->prev)
		g_types_tab[maptype] = NULL;
	else
		g_types_tab[maptype]->last = todel->next;
	munmap(todel, map_full_size);
	todel = NULL;
}

static void		browse_found_map(t_map **map, t_block *to_free, int maptype)
{
	t_block		*block;
	int			is_updated;

	is_updated = 0;
	to_free->free = TRUE;
	block = (*map)->block;
	while (block)
	{
		is_updated = update_map_blocks(block);
		if (maptype == LARGE ||
			(block->free && !block->next && block == (*map)->block))
		{
			mumnmap_and_update_maps(map, maptype);
			return ;
		}
		if (is_updated)
			return ;
		block = block->next;
	}
}

static int		find_map(t_map **map, void *ptr, size_t page)
{
	int		maptype;
	void	*cur_page_addr;

	maptype = (*map)->type;
	cur_page_addr = (void*)*map + getpagesize() * page;
	if ((long)cur_page_addr == ((long)ptr & 0xFFFFFFFFF000))
	{
		browse_found_map(map, ptr - BLOCK_SIZE, maptype);
		return (TRUE);
	}
	else if (maptype != LARGE && (*map)->page_count > (size_t)page - 1)
		return (find_map(map, ptr, page + 1));
	else if ((*map)->next)
		return (find_map(&(*map)->next, ptr, 0));
	return (FALSE);
}

void			ts_free(void *ptr)
{
	int		type;

	type = 0;
	if (ptr == NULL)
		return ;
	while (type < MAX_TYPE)
	{
		if (g_types_tab[type])
		{
			if (find_map(&g_types_tab[type], ptr, 0))
				return ;
		}
		type++;
	}
}
