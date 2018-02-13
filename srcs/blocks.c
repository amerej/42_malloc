/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 15:01:01 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block	*get_fiteable_block(t_map *map, size_t size)
{
	t_block	*block;

	block = map->block;
	while (block)
	{
		if ((block->free && block->size >= size))
			return (block);
		block = block->next;
	}
	return (NULL);
}

static void		update_map_blocks(t_map *map, t_block *block, int type,
																size_t size)
{
	size_t		oldsize;
	t_block		*next;

	oldsize = block->size;
	next = block->next;
	map->free_space = map->free_space - (size + BLOCK_SIZE);
	block->free = FALSE;
	block->size = size;
	if (type == LARGE)
		next = create_block(map, map->free_space, block, NULL);
	else if (!next)
		next = create_block(map, oldsize - BLOCK_SIZE - size, block, NULL);
}

t_block			*create_block(t_map *map, size_t size, t_block *prev_block,
														t_block *next_block)
{
	t_block	*block;

	if (!prev_block)
		block = (void *)map + MAP_SIZE;
	else
		block = (void *)prev_block + BLOCK_SIZE + prev_block->size;
	block->free = TRUE;
	block->size = size;
	block->ptr = (void *)block + BLOCK_SIZE;
	block->next = next_block;
	return (block);
}

t_block			*get_block(t_map *map, int type, size_t size)
{
	t_block		*block;
	t_map		*cur_map;

	block = NULL;
	while (map)
	{
		if ((type != LARGE && map->free_space >= size + BLOCK_SIZE
			&& (block = get_fiteable_block(map, size))) || (type == LARGE
			&& map->block == (block = get_fiteable_block(map, size))))
		{
			update_map_blocks(map, block, type, size);
			return (block);
		}
		cur_map = map;
		map = map->next;
	}
	if (!(cur_map->next = create_map(type, size, cur_map)))
		return (NULL);
	return (get_block(cur_map->next, type, size));
}
