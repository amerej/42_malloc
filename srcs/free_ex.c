/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/21 19:34:44 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		update_map_blocks(t_block *block)
{
	ft_putstr("\nf(update_map_blocks)");

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

static void		mumnmap_and_update_maps(t_map **map)
{
	size_t		map_full_size;
	t_map		*todel;

	todel = *map;
	map_full_size = todel->block->size + MAP_SIZE;
	ft_putstr("\nf(munmap_and_update_maps), addr: ");
	ft_putnbr_base((long)(*map)->next, 16);	

	if ((*map)->prev)
		*map = (*map)->prev;
	(*map)->next = todel->next;
	if ((*map)->next)
		(*map)->next->prev = *map;

	ft_putstr("\nmapfullsize: ");
	ft_putnbr_base((long)map_full_size, 10);	

	munmap(todel, map_full_size);
	ft_putstr("\nEND OF f(munmap_and_update_maps), addr TO DEWL: ");	
	ft_putnbr_base((long)todel, 16);
	todel = NULL;
	ft_putstr("\nEND OF f(munmap_and_update_maps), addr GLOBAL: ");	
	ft_putnbr_base((long)g_types_tab[LARGE], 16);
	
}

static void		browse_found_map(t_map **map, t_block *to_free)
{
	t_block		*block;

	to_free->free = TRUE;

	ft_putstr("\nf(browse_map), ptr to free: ");
	ft_putnbr_base((long)(*map), 16);

	block = (*map)->block; // NO MAPS BLOCK
	while (block)
	{
		update_map_blocks(block);

		ft_putstr("\nblock: ");
		ft_putnbr_base((long)block, 16);
		ft_putstr(" <> map->block: ");
		ft_putnbr_base((long)(*map)->block, 16);
		if (block->free && !block->next && block == (*map)->block) // NE RENTRE PAS DANS LA CDT
		{
			mumnmap_and_update_maps(map);
			return;
		}
		block = block->next;
	}
	ft_putstr("\nBM ::: END\n");
}

void	find_map(t_map **map, void *ptr)
{
	if ((long)*map == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
	{
		ft_putstr("\naddr MAP: ");	
		ft_putnbr_base((long)*map, 16);
		ft_putstr("\naddr GLOBAL2: ");	
		ft_putnbr_base((long)g_types_tab[LARGE], 16);
		browse_found_map(map, (void*)ptr - BLOCK_SIZE);
		return;
	}
	else if ((*map)->next)
		find_map(&(*map)->next, ptr);
}

void    free(void *ptr)
{
	int		type;

	ft_putstr("\nf(free)");
	type = 0;
	while (type < MAX_TYPE)
	{
		ft_putstr("\naddr GLOBAL ENTRY FIND: ");
		ft_putnbr_base((long)g_types_tab[type], 16);
		if (g_types_tab[type])
			find_map(&g_types_tab[type], ptr);
		type++;
	}
}