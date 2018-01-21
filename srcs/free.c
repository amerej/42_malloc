/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/21 20:56:48 by gpoblon          ###   ########.fr       */
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


	ft_putstr("\naddr GLOBAL IN: ");
	ft_putnbr_base((long)g_types_tab[LARGE], 16);

	ft_putstr("\nf(munmap_and_update_maps), map IN addr: ");
	ft_putnbr_base((long)*map, 16);

	(*map) = (*map)->next;
	if (*map)
		(*map)->prev = todel->prev;

	ft_putstr("\nf(munmap_and_update_maps), map OUT addr: ");
	ft_putnbr_base((long)*map, 16);	

	ft_putstr("\naddr GLOBAL OUT: ");
	ft_putnbr_base((long)g_types_tab[LARGE], 16);

	munmap(todel, map_full_size);
	todel = NULL;
	
}

static void		browse_found_map(t_map **map, t_block *to_free)
{
	t_block		*block;

	to_free->free = TRUE;

	ft_putstr("\nf(browse_map)");

	block = (*map)->block; // NO MAPS BLOCK
	while (block)
	{
		update_map_blocks(block);

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
	ft_putstr("\nf(find_map)");	
	if ((long)*map == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
	{
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
	ft_putnbr_base((long)BLOCK_SIZE, 10);
	

	type = 0;
	while (type < MAX_TYPE)
	{
		if (g_types_tab[type])
			find_map(&g_types_tab[type], ptr);
		type++;
	}
}