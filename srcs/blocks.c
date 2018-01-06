/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2017/12/17 20:25:45 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block	*get_fiteable_block(t_map *map, size_t size)
{
	t_block	*block;

	block = map->block;

	while (block)
	{
		if (!block->free)
			continue;

		if (type == TINY || type == SMALL ||
			(TYPE == LARGE && block->size >= size))
			return (block);
		block = block->next;
	}
	return (NULL);
}

static void		update_status(t_map *map, t_block *block, size_t size)
{
	map->free_space = map->free_space - (size + META_BLOCK_SIZE);
	map->block = block;

	block->free = FALSE;
	block->size = size;
	block->ptr = (void *)block + META_BLOCK_SIZE;
}

// map here is still at the beginning of its list

t_block		    *get_block(t_map *map, int type, size_t size)
{
	t_block		*block;

	block = NULL;
	while (map)
	{
		if (map->free_space >= size + META_BLOCK_SIZE && 	//TODO : should count META_BLOCK_SIZE ???
			block = get_fiteable_block(map, size))
		{
				update_status(map, block, size);
				return block;
		}
		map = map->next;
	}
	
	if (!block) // unecessary but explicit condition
	{
		map = create_map(type, size); //TODO is this pushing a map at the end ?
		return (map->block);
	}
}

t_block     	*create_block(t_map **map, size_t size)
{
	t_block	*block;

	(*map)->free_space = (*map)->free_space - (size + META_BLOCK_SIZE);

	block->free = TRUE;
	block->size = size;
	block->ptr = (void *)(*map) + META_BLOCK_SIZE;
	block->prev = NULL;
	block->next = NULL;

	return (block);
}

// TODO gerer prev/next des blocks
// malloc = pas besoin du prev block ?