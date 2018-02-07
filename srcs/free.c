/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 15:28:29 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		update_map_blocks(t_block *block)
{
	ft_putstr("\nf(update_map_blocks), is free ?");
	ft_putnbr_base((long)block->free, 10);	

	if (block->free == TRUE && block->next && block->next->free == TRUE)
	{
		ft_putstr("\nmerge blocks");
		block->size += block->next->size + BLOCK_SIZE;
		block->next = block->next->next;
		if (block->next)
		{
			block->next->prev = block;
			if (block->next->free == TRUE)
				update_map_blocks(block);
		}
	}
}

static void		mumnmap_and_update_maps(t_map **map, int maptype)
{
	size_t		map_full_size;
	t_map		*todel;

	todel = *map;
	map_full_size = todel->block->size + MAP_SIZE;


	ft_putstr("\nf(munmap_and_update_maps), map IN addr: ");
	ft_putnbr_base((long)*map, 16);

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

	ft_putstr("\nf(munmap_and_update_maps), map OUT addr: ");
	ft_putnbr_base((long)*map, 16);	
}

static void		browse_found_map(t_map **map, t_block *to_free, int maptype)
{
	t_block		*block;
	int count =0;

	ft_putstr("\nf(browse_map), to free addr: ");
	ft_putnbr_base((long)to_free, 16);

	to_free->free = TRUE;

	block = (*map)->block; // NO MAPS BLOCK
	while (block)
	{
		update_map_blocks(block);
		ft_putstr("\nf(block if count) "); ft_putnbr_base((long)count++, 10);
		ft_putstr(", map type "); ft_putnbr_base((long)maptype, 10);
		ft_putstr(", to_free type "); ft_putnbr_base((long)get_type(to_free->size), 10);
		ft_putstr(", block->next "); ft_putnbr_base((long)block->next, 16);
		ft_putstr(" (*map)->block "); ft_putnbr_base((long)(*map)->block, 16);
		ft_putstr(" block "); ft_putnbr_base((long)block, 16);

		if (maptype == LARGE ||
			(block->free && !block->next && block == (*map)->block)) // NE RENTRE PAS DANS LA CDT
		{
			mumnmap_and_update_maps(map, maptype);
			return;
		}
		block = block->next;
	}
	ft_putstr("\nBM ::: END\n");
}

static int		find_map(t_map **map, void *ptr, size_t page)
{
	int		maptype;

	maptype = get_type((*map)->block->size);
	ft_putstr("F");
  	if ((long)((void*)*map + getpagesize() * page) == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
  	{
		ft_putstr("\nMap found: ");
		ft_putnbr_base((long)*map, 16);
		ft_putstr(" map +getpagesize: ");
		ft_putnbr_base((long)((void*)*map + getpagesize() * page), 16);
		ft_putstr(" type: ");
		ft_putnbr_base((long)maptype, 10);		
		ft_putstr(" page: ");
		ft_putnbr_base((long)page, 10);
		ft_putstr(" pagecount: ");
		ft_putnbr_base((long)(*map)->page_count, 10);
	 	browse_found_map(map, ptr - BLOCK_SIZE, maptype);
		return TRUE;
	}
	else if (maptype != LARGE && (*map)->page_count > (size_t)page - 1)
		return find_map(map, ptr, page + 1);
	else if ((*map)->next)
		return find_map(&(*map)->next, ptr, 0);
	return FALSE;
}

void			free(void *ptr)
{
	int		type;
	ft_putstr("\nf(free), addr"); ft_putnbr_base((long)ptr, 16);

	type = 0;
	if (ptr == NULL)
		return; 
	while (type < MAX_TYPE)
	{
		ft_putstr("\nglobal type: ");
		ft_putnbr_base((long)type, 10);	
		if (g_types_tab[type]) {
			if (find_map(&g_types_tab[type], ptr, 0))
			{
				// show_alloc_mem();					
				return;
			}
		}
		type++;
	}

	// show_alloc_mem();	
}