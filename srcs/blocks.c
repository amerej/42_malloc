/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/07 03:50:31 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block	*get_fiteable_block(t_map *map, int type, size_t size)
{
	t_block	*block;

	ft_putstr("\nf(get fiteable block)");
	block = map->block;
	while (block)
	{
		if (block-> free && (type == TINY || type == SMALL ||
			(type == LARGE && block->size >= (size + BLOCK_SIZE))))
			return (block);
		block = block->next;
	}
	return (NULL);
}

static void		update_map_blocks(t_map *map, t_block *block, size_t size)
{
	ft_putstr("\nf(update map blocks)");
	// ft_putnbr_base("\nblock = ", 16);
	// ft_putnbr_base((long)block, 16);
	// ft_putstr(", prev = ");
	// ft_putnbr_base((long)block->prev, 16);
	// ft_putstr(", next = ");
	// ft_putnbr_base((long)block->next, 16);
	// ft_putstr(", size = ");
	// ft_putnbr((long)block->size, 10);

	map->free_space = map->free_space - (size + BLOCK_SIZE);	
	
	block->free = FALSE;
	block->size = size;
	block->next = create_block(map, map->free_space, block, block->next);
	
}

t_block     	*create_block(t_map *map, size_t size, t_block *prev_block,
	t_block *next_block)
{
	t_block	*block;

	ft_putstr("\nf(create block)");

	if (!prev_block) block = (void *)map + MAP_SIZE;
	else block = (void *)prev_block + BLOCK_SIZE + prev_block->size;

	// ft_putstr("\nblock = ");
	// ft_putnbr_base((long)block, 16);
	// ft_putstr(", bprev = ");
	// ft_putnbr_base((long)prev_block, 16);	
	// ft_putstr(", bnext = ");
	// ft_putnbr_base((long)next_block, 16);
	// ft_putstr(", size = ");	
	// ft_putnbr(size, 10);
	// ft_putstr(", map->free_space = ");	
	// ft_putnbr(map->free_space, 10);
	
	block->free = TRUE;
	block->size = size;
	block->ptr = (void *)block + BLOCK_SIZE;
	
	block->prev = prev_block;
	block->next = next_block; //(block != next_block) ? next_block : NULL;

	return (block);
}

// map here is still at the beginning of its list

t_block		    *get_block(t_map *map, int type, size_t size)
{
	t_block		*block;
	t_map		*cur_map;

	ft_putstr("\nf(get block)");

	block = NULL;

	while (map) // si on ajoute get_map en wrapper on peut faire get_map en recursive, + propre
	{
		if (map->free_space >= (size + BLOCK_SIZE) &&
			(block = get_fiteable_block(map, type, size)))
		{
			update_map_blocks(map, block, size);
			return block;
		}
		cur_map = map;
		map = map->next;
	}
	
	ft_putstr("\nend of map loop, no result -> create_map");
	
	cur_map->next = create_map(type, size);
	return (get_block(cur_map->next, type, size));
}