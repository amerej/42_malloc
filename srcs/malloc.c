/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by aditsch           #+#    #+#             */
/*   Updated: 2017/12/17 20:25:45 by aditsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

maps = {NULL, NULL, NULL};

t_map_data		get_map_data(size_t size)
{
	t_map_data	map_data;

	if (size <= TINY_SIZE)
	{
		map_data.map_size = TINY_SIZE;
		map_data.map_type = TINY;
	}
	else if (size <= SMALL_SIZE)
	{
		map_data.map_size = SMALL_SIZE;
		map_data.map_type = SMALL;
	}
	else
	{
		map_data.map_size = size;
		map_data.map_type = LARGE;
	}
	return map_data;
}

t_block		*init_block(size_t size, t_map *addr)
{
	t_block		*block;

	block->size = size - BLOCK_SIZE;
	block->next = NULL;
	block->prev = NULL;
	block->free = TRUE;
	block->ptr = (void *)addr + BLOCK_SIZE;

	return (block);
}

t_map		*create_map(size_t size)
{
	int 		page_size;
	size_t		map_size;
	t_map		*map;
	
	page_size = getpagesize();
	map_size = ((sizeof(t_map) + ((BLOCK_SIZE + size) * 100)) / page_size + 1) * page_size;
	if ((map = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	
	map->block = init_block(size, map);
	map->next = NULL;
	map->state = FREE;
	
	return (map);
}

int			init_map(t_map_data map_data)
{
	if (maps->tiny == NULL && map_data.map_type == TINY)
		if ((maps->tiny = create_map(map_data.map_size)) == NULL)
			return (FALSE);
	else if (maps->small == NULL && map_data.map_type == SMALL)
		if ((maps->small = create_map(map_data.map_size)) == NULL)
			return (FALSE);
	else if (maps->large == NULL && map_data.map_type == LARGE)
		if ((maps->large = create_map(map_data.map_size)) == NULL)
			return (FALSE);
	return (TRUE);
}

t_map		*select_map(t_map_data map_data)
{
	if (map_data.map_type == TINY)
		return (maps->tiny);
	if (map_data.map_type == SMALL)
		return (maps->small);
	return (maps->large);
}

t_map		*get_free_block(t_map **map, t_map_data map_data)
{
	if (((*map)->block) == NULL)
		(*map)->state = FULL;
	else if (((*map)->block->free) == FALSE || (*map)->block->size < (map_data.map_size + BLOCK_SIZE))
		get_free_block(&(*map)->block->next, map_data);
	return (*map);
}

void		*get_free_addr(t_map **map, size_t size)
{
	if ((*map)->block->free == TRUE && (*map)->block->size <= (size + BLOCK_SIZE))
	{
		(*map)->block->size = (*map)->block->size - (size - BLOCK_SIZE);
		(*map)->block->next = NULL;
		(*map)->block->free = FALSE;
		(*map)->block->
	}

}

t_map		*get_free_space(t_map **map, t_map_data map_data, size_t size)
{
	if ((*map) == NULL)
		if ((*map = create_map(map_data.map_size)) == NULL)
			return (NULL);
	(*map) = get_free_block(&(*map), map_data);
	if ((*map)->state == FULL)
		get_free_space(&(*map)->next, map_data, size);
	
	
	return (*map);
}

void		*malloc(size_t size)
{
	t_map_data		map_data;
	t_map			*map;
	void			*addr;

	map_data = get_map_data(size);
	if (!init_map(map_data))
		return (NULL);
	map = select_map(map_data);
	if ((addr = get_free_space(&map, map_data, size)) == NULL)
		return (NULL);
	
}
