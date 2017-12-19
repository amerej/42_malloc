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

g_tab_maps = {NULL, NULL, NULL};

int			get_type(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	else if (size <= SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}

int			get_size(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY_SIZE);
	else if (size <= SMALL_SIZE)
		return (SMALL_SIZE);
	else
		return (size);
}

t_mlist		*select_map(t_mlist **list, size_t size, int type)
{
	if (!(*list))
		*list = create_map(size, type);
	if ((*list)->state == FULL/* || get_available_space_size(list, size)*/)
		select_map(&(*list)->next, size, type);
	return (*list);
}
 
t_mlist		*create_map(size_t size, int type)
{
	t_mlist *map;

	int page_size = getpagesize();
	
	size_t	full_size = (((((size + META_BLOCK_SIZE) * 100) + META_MLIST_SIZE) / page_size + 1) * page_size);


	if ((map = mmap(NULL, full_size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	
	if (g_tab_maps[type] == NULL)
		g_tab_maps[type] = map;

	init_map(&map, (full_size - ALIGN_4(sizeof(t_mlist))));	
	
	return map;
	
}

init_map(t_mlist **list, size_t size)
{
	(*list)->next = NULL;
	(*list)->state = FALSE;
	(*list)->block = init_block(size, *list);
}

t_block	*init_block(size_t size, t_mlist *addr)
{
	t_block	*block;

	block->size = size;
	block->free = TRUE;
	block->ptr = addr + META_BLOCK_SIZE;
	block->next = NULL;
	block->prev = NULL;

	return (block);
}

void	move_to_allocable_space(t_mlist *list)
{
	t_dlst *lst;

	lst = (void *)list + META_MLIST_SIZE;
	
}

t_mlist		*get_map(int type, size_t size)
{
	return ((g_tab_maps[type]) ? select_map(g_tab_maps[type], size, type) : create_map(get_size(size), type));
}

void	*malloc(size_t size)
{
	t_mlist 	*map;
	
	map = get_map(get_type(size), size);
	move_to_allocable_space(map);
}
