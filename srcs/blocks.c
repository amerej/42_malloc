/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/04 17:21:02 by gpoblon          ###   ########.fr       */
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
		if ((block->free && block->size >= size))
			return (block);
		block = block->next;
	}
	return (NULL);
}

static void		update_map_blocks(t_map *map, t_block *block, int type, size_t size)
{
	size_t		oldsize;
	ft_putstr("\nf(update map blocks)");
	oldsize = block->size;
	map->free_space = map->free_space - (size + BLOCK_SIZE);

	block->free = FALSE;
	block->size = size;
	if (type == LARGE) // OK
		block->next = create_block(map, map->free_space, block, NULL);
	else if (!block->next)
		block->next = create_block(map, oldsize - BLOCK_SIZE - size, block, NULL);
	ft_putstr(" block->next oldsize "); ft_putnbr_base((long)oldsize, 10);		
	ft_putstr(" - size "); ft_putnbr_base((long)size, 10);		
	ft_putstr(" type "); ft_putnbr_base((long)type, 10);
}

t_block     	*create_block(t_map *map, size_t size, t_block *prev_block,
	t_block *next_block)
{
	t_block	*block;

	ft_putstr("\nf(create block)");

	if (!prev_block)
		block = (void *)map + MAP_SIZE;
	else
		block = (void *)prev_block + BLOCK_SIZE + prev_block->size;
	
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

		if ((type != LARGE && map->free_space >= size + BLOCK_SIZE
			&& (block = get_fiteable_block(map, type, size))) || (type == LARGE
			&& map->block == (block = get_fiteable_block(map, type, size))))
		{
			update_map_blocks(map, block, type, size);
			return block;
		}
		cur_map = map;
		map = map->next;
	}
	
	ft_putstr("\nend of map loop, no result -> create_map");
	
	if (!(cur_map->next = create_map(type, size, cur_map)))
		return NULL;
	
	return (get_block(cur_map->next, type, size));
}