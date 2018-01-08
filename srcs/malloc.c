/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by aditsch           #+#    #+#             */
/*   Updated: 2018/01/08 07:40:46 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

maps = {NULL, NULL, NULL};

t_alloc_data	get_alloc_data(size_t size)
{
	if (size <= TINY_SIZE)
		return ((t_alloc_data){TINY_SIZE, TINY, size});
	if (size <= SMALL_SIZE)
		return ((t_alloc_data){SMALL_SIZE, SMALL, size});
	return ((t_alloc_data){size, LARGE, size});
}

t_map			*create_map(size_t size)
{
	int 		page_size;
	size_t		map_size;
	t_map		*map;
	
	page_size = getpagesize();
	map_size = ((sizeof(t_map) + 
		((BLOCK_SIZE + size) * 100)) / page_size + 1) * page_size;
	if ((map = mmap(NULL, map_size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	map->block->size = map_size - BLOCK_SIZE;
	map->block->next = NULL;
	map->block->prev = NULL;
	map->block->free = TRUE;
	map->block->ptr = (void *)map + BLOCK_SIZE;
	map->next = NULL;
	map->state = FREE;
	return (map);
}

t_map			*get_map_list(t_alloc_data data)
{
	t_map	*map;

	if (data.type == TINY)
		map = maps->tiny;
	else if (data.type == SMALL)
		map = maps->small;
	else
		map = maps->large;
	if (!map)
		return ((map = create_map(data.size)) == NULL) ? NULL : map;
	return (map);
}

void			*get_free_addr(t_map **map, size_t size)
{
	if ((*map)->block->free == TRUE && (*map)->block->size <= (size + BLOCK_SIZE))
	{
		(*map)->block->size = (*map)->block->size - (size - BLOCK_SIZE);
		(*map)->block->next = NULL;
		(*map)->block->free = FALSE;
		(*map)->block->
	}
}

t_block			*get_free_block(t_block **block, t_alloc_data data)
{
	if (!(*block))
		return (NULL);
	
	if ((*block)->size < (data.size + BLOCK_SIZE) || !(*block)->free)
		get_free_block(&(*block)->next, data);
	
	if ((*block)->size >= (data.size + BLOCK_SIZE) && (*block)->free)
		

	return (*block);
}

void			*get_free_space(t_map **map, t_alloc_data data)
{
	t_block		*block;
	
	if ((*map) == NULL)
		if ((*map = create_map(data.size)) == NULL)
			return (NULL);

	if (!(block = get_free_block(&(*map)->block, data)))
		get_free_space(&(*map)->next, data);

	return (block->ptr);
}

void			*malloc(size_t size)
{
	t_alloc_data	alloc_data;
	t_map			*map_list;
	void			*addr;

	if (size <= ZERO)
		return (NULL);
	alloc_data = get_alloc_data(size);
	if (!(map_list = get_map_list(alloc_data)))
		return (NULL);
	if ((addr = get_free_space(&map_list, alloc_data)) == NULL)
		return (NULL);
	return (addr);
}