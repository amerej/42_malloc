/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/06 19:15:56 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block	*get_fiteable_block(t_map *map, int type, size_t size)
{
	t_block	*block;

	block = map->block;
	while (block)
	{
		if (!block->free)
			continue;
		if (type == TINY || type == SMALL ||
			(type == LARGE && block->size >= size))
			return (block);
	}
	return (NULL);
}

static void		update_map_blocks(t_map *map, t_block *block, size_t size)
{
	block->free = FALSE;
	block->size = size;
	block->ptr = (void *)block + BLOCK_SIZE;
	block->next = create_block(map, map->free_space, block, block->next);
}

t_block     	*create_block(t_map *map, size_t size, t_block *prev_block,
	t_block *next_block)
{
	t_block	*block;

	block = prev_block ? prev_block->next : (void *)map + MAP_SIZE;

	ft_putstr("\n\ncreate block\n\n&map: ");
	ft_putnbr_hex((long)map);
	ft_putstr("\nblock: ");
	ft_putnbr_hex((long)block);
	ft_putstr("\nbprev: ");
	ft_putnbr_hex((long)prev_block);	
	ft_putstr("\nnext: ");
	ft_putnbr_hex((long)next_block);
	ft_putstr("\nsize: ");	
	ft_putnbr(size);

	

	map->free_space = map->free_space - (size + BLOCK_SIZE);

	block->free = TRUE;
	block->size = size;
	block->ptr = (void *)map->block + BLOCK_SIZE;
	
	
	block->prev = prev_block;
	block->next = next_block;

	return (block);
}

// map here is still at the beginning of its list

t_block		    *get_block(t_map *map, int type, size_t size)
{
	t_block		*block;
	t_map		*cur_map;

	block = NULL;
	while (map)
	{
		if (map->free_space >= size + BLOCK_SIZE && 	//TODO : should count BLOCK_SIZE ???
			(block = get_fiteable_block(map, type, size)))
		{
				update_map_blocks(map, block, size);
				return block;
		}
		cur_map = map;
		map = map->next;
	}
	
	cur_map->next = create_map(type, size); //TODO is this pushing a map at the end ?
	return (map->block);
}

// TODO gerer prev/next des blocks
// malloc = pas besoin du prev block ?