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
	ft_putstr("\nUPDATE MAP BLOCKS");

	if (block->free == TRUE && block->next && block->next->free == TRUE)
	{
		ft_putstr("\nUPDATE IN IF");
		block->size += block->next->size + BLOCK_SIZE;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
		ft_putstr("\nUPDATE END IF");		
	}
}

static void		mumnmap_and_update_maps(t_map *map, t_map *prev_map)
{
	size_t		map_full_size;

	map_full_size = map->block->size + BLOCK_SIZE + MAP_SIZE;
	
	munmap(map, map_full_size);

	if (prev_map)
		prev_map->next = map->next;
	else
		map = map->next;
}

static void		browse_map(t_map *map, t_block *to_free, t_map *prev_map)
{
	t_block		*it_block;

	to_free->free = TRUE;

	ft_putstr("\nBROWSE MAP &block TO FREE");
	ft_putnbr_hex((long)to_free);

	it_block = map->block;
	while (it_block)
	{
		ft_putstr("\nBROWSE MAP it_block");
		ft_putnbr_hex((long)it_block);

		update_map_blocks(it_block);

		ft_putstr("\nBROWSE MAP after update");
		if (!it_block->next && map->block == it_block) // NE RENTRE PAS DANS LA CDT
		{
			ft_putstr("\nBROWSE MAP IF MUNMAP map:");
			ft_putnbr_hex((long)map);
			
			mumnmap_and_update_maps(map, prev_map);
			ft_putstr("\nBROWSE MAP ENDIF MUNMAP: map freed");
			ft_putnbr_hex((long)map);	
		}
		it_block = it_block->next;
	}
	ft_putstr("\nBROWSE MAP ::: END");
}

void    free(void *ptr)
{
	t_map		*map;
	t_map		*prev_map;
	int			types;

	types = 0;
	prev_map = NULL;
	while ((map = g_types_tab[types++]))
	{
		// ft_putstr("\nFREE WHILE map = g_types");
		// ft_putnbr_hex((long)map);
		if ((long)map == ((long)ptr & 0xFFFFFF000))
		{
			ft_putstr("\nFREE IF GOOD map FOUND !!!");
			ft_putnbr_hex((long)map->block);	
			browse_map(map, (void*)ptr - BLOCK_SIZE, prev_map);
			return;
		}
		prev_map = map;
		map = map->next;
	}
}