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

// t_mlist		*select_map(t_mlist **list, size_t size, int type)
// {
// 	if (!(*list))
// 		*list = create_map(size, type);
// 	if ((*list)->state == FULL/* || get_available_space_size(list, size)*/)
// 		select_map(&(*list)->next, size, type);
// 	return (*list);
// }
 
// t_mlist		*create_map(size_t size, int type)
// {
// 	t_mlist *map;

// 	int page_size = getpagesize();
	
// 	size_t	full_size = (((((size + META_BLOCK_SIZE) * 100) + META_MLIST_SIZE) / page_size + 1) * page_size);


// 	if ((map = mmap(NULL, full_size, PROT_READ | PROT_WRITE,
// 		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
// 		return (NULL);
	
// 	if (g_tab_maps[type] == NULL)
// 		g_tab_maps[type] = map;

// 	init_map(&map, (full_size - ALIGN_4(sizeof(t_mlist))));	
	
// 	return map;
	
// }

// init_map(t_mlist **list, size_t size)
// {
// 	(*list)->next = NULL;
// 	(*list)->state = FALSE;
// 	(*list)->block = init_block(size, *list);
// }


void	move_to_allocable_space(t_mlist *list)
{
	t_dlst *lst;

	lst = (void *)list + META_MLIST_SIZE;
	
}

t_mlist		*get_map(int type, size_t size)
{
	return ((g_tab_maps[type]) ? select_map(g_tab_maps[type], size, type) : create_map(get_size(size), type));
}

t_block		*init_block(size_t size, t_map *addr)
{
	t_block		*block;

	block->size = size;
	block->next = NULL;
	block->prev = NULL;
	block->free = TRUE;
	block->ptr = BLOCK_SIZE + addr;

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

t_map		*get_map(t_map_data map_data)
{
	t_map	*map_list;
	t_map	*prev;
	
	map_list = select_map(map_data);

	while (map_list != NULL && (map_list->state != FREE || map_list->state != USABLE))
	{
		prev = map_list;
		map_list = map_list->next;
	}
	if (map_list == NULL)
	{
		if ((map_list = create_map(map_data.map_size)) == NULL)
			return (NULL);
		return (map_list);
	}
	return (prev);
}

void		*malloc(size_t size)
{
	t_map_data		map_data;

	map_data = get_map_data(size);
	if (!init_map(map_data))
		return (NULL);
	

	map = get_map(get_type(size), size);
	move_to_allocable_space(map);
}
