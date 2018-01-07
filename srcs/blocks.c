/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/07 01:26:52 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

// only for testing purpose
static void		print_map_blocks(t_map *map)
{
	t_block	*block;
	
	block = map->block;
	ft_putstr("\n\n-----------------------------\nFUN PRINT MAP BLOCKS -- &map: ");
	ft_putnbr_hex((long)map);

	while (block)
	{
		ft_putstr("\n&block: ");
		ft_putnbr_hex((long)block);
		
		block->free ? ft_putstr("\nfree = TRUE") : ft_putstr("\nfree = FALSE");
		ft_putstr("\nbprev: ");
		ft_putnbr_hex((long)block->prev);	
		ft_putstr("\nnext: ");
		ft_putnbr_hex((long)block->next);
		ft_putstr("\nsize: ");
		ft_putnbr(block->size);
		ft_putstr("\n\nblock->ptr = ");
		ft_putstr((char*)block->ptr);

		block = block->next;
	}

	ft_putstr("\n-----------------------------\n");
}

static t_block	*get_fiteable_block(t_map *map, int type, size_t size)
{
	t_block	*block;

	ft_putstr("\n\nFUN get fiteable block");
	block = map->block;
	while (block)
	{
		if (!block->free)
			block = block->next;
		if (type == TINY || type == SMALL ||
			(type == LARGE && block->size >= size))
			return (block);
		block = block->next;
	}
	return (NULL);
}

static void		update_map_blocks(t_map *map, t_block *block, size_t size)
{
	ft_putstr("\n\nFUN update map blocks");
	map->free_space = map->free_space - (size + BLOCK_SIZE);
	
	block->free = FALSE;
	block->size = size;
	block->ptr = (void *)block + BLOCK_SIZE;
	block->next = create_block(map, map->free_space, block, block->next);
}

t_block     	*create_block(t_map *map, size_t size, t_block *prev_block,
	t_block *next_block)
{
	t_block	*block;

	ft_putstr("\n\nFUN create block");

	if (!prev_block) block = (void *)map + MAP_SIZE;
	else if (prev_block && prev_block->next) block = prev_block->next;
	else block = (void *)prev_block + BLOCK_SIZE + prev_block->size;

	// block = prev_block ? 
	// 	prev_block->next :
	// 	(void *)map + MAP_SIZE;

	ft_putstr("\n&map: ");
	ft_putnbr_hex((long)map);
	ft_putstr("\nblock: ");
	ft_putnbr_hex((long)block);
	ft_putstr("\nbprev: ");
	ft_putnbr_hex((long)prev_block);	
	ft_putstr("\nnext: ");
	ft_putnbr_hex((long)next_block);
	ft_putstr("\nsize: ");	
	ft_putnbr(size);

	block->free = TRUE;
	block->size = size;
	block->ptr = (void *)block + BLOCK_SIZE;
	
	ft_putstr("\nptr: ");
	ft_putnbr_hex((long)block->ptr);

	block->prev = prev_block;
	block->next = next_block;

	return (block);
}

// map here is still at the beginning of its list

t_block		    *get_block(t_map *map, int type, size_t size)
{
	t_block		*block;
	t_map		*cur_map;

	ft_putstr("\n\nFUN get block");

	block = NULL;

	while (map)
	{
		ft_putstr("\n&map: ");
		ft_putnbr_hex((long)map);

		if (map->free_space >= size + BLOCK_SIZE && 	//TODO : should count BLOCK_SIZE ???
			(block = get_fiteable_block(map, type, size)))
		{
				update_map_blocks(map, block, size);

				print_map_blocks(map);
				
				return block;
		}
		cur_map = map;
		map = map->next;
	}
	
	ft_putstr("\nend of map loop, no result -> create_map");	
	
	cur_map->next = create_map(type, size); //TODO is this pushing a map at the end ?

	return (get_block(cur_map->next, type, size));
}

// TODO gerer prev/next des blocks
// malloc = pas besoin du prev block ?