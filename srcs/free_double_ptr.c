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

static void		mumnmap_and_update_maps(t_map **map, t_map **prev_map)
{
	size_t		map_full_size;
	t_map		*tmp_map;

	tmp_map = (*map);
	ft_putstr("\nf(munmap_and_update_maps)\naddr: ");
	ft_putnbr_base((long)(*map), 16);	
	map_full_size = (*map)->block->size + BLOCK_SIZE + MAP_SIZE;
	if (prev_map)
		(*prev_map)->next = (*map)->next;
	// else
	// 	map = map->next;

	(*map) = NULL;
	munmap(tmp_map, map_full_size);
}

static void		browse_map(t_map **map, t_block *to_free, t_map **prev_map)
{
	t_block		*block;

	to_free->free = TRUE;

	ft_putstr("\nf(browse_map), ptr to free: ");
	ft_putnbr_base((long)to_free, 16);

	block = (*map)->block;
	while (block)
	{
		update_map_blocks(block);

		ft_putstr("\nblock: ");
		ft_putnbr_base((long)block, 16);
		ft_putstr(" <> map->block: ");
		ft_putnbr_base((long)(*map->block, 16);
		if (block->free && !block->next && block == (*map)->block) // NE RENTRE PAS DANS LA CDT
		{
			mumnmap_and_update_maps(*map, *prev_map);
			ft_putstr("\nBM: map freed");
			return;
		}
		block = block->next;
	}
	ft_putstr("\nBM ::: END\n");
}

void    free(void *ptr)
{
	t_map		*map;
	t_map		*prev_map;
	int			types;

	ft_putstr("\nf(free)");
	types = 0;
	prev_map = NULL;
	while ((map = g_types_tab[types++]))
	{
		if ((long)map == ((long)ptr & 0xFFFFFF000))
		{
			ft_putstr("\nmap found: ");
			ft_putnbr_base((long)map, 16);	

			browse_map(&map, (void*)ptr - BLOCK_SIZE, &prev_map);
			return;
		}
		prev_map = map;
		map = map->next;
	}
}