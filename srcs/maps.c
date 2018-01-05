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

static t_bool		is_data_fiteable_in_map(t_map *node, size_t size)
{
	t_block	*block;

	block = node->block;

	if ((type == TINY || type == SMALL) && (*node)->free_space >= size)
		return TRUE;
	else if (type == LARGE)
	{
		while (block)
		{
			if (block->free == TRUE && block->size >= size)
				return TRUE
			else
				block = block->next;
		}
	}
	else
		return FALSE
}

static t_map		*select_map(t_map **node, size_t size, int type)
{
	if (!(*node))
		*node = create_map(size, type);
	if (!is_data_fiteable_in_map(node, size))
		select_map(&(*node)->next, size, type);
	return (*node);
}
 
static t_map		*create_map(size_t size, int type)
{
	t_map	*map;

	int		page_size = getpagesize();

	/*
	** mapsize formula
	** 100 * -> rule given by the subject: mmap must be at least 100 * size +
	** SIZEOF(structs header). Size is wrapped in each struct contained in t_map
	**
	** the last part makes sure resulted size is a multiple of getpagesize
	** (which is an unnecessary process because mmap does it too)
	** -1 counterbalances +1 in case of map being getpagesize multiple.
	** map / getpagesize = floating number truncated = multiple value
	*/
	
	size_t	map_size = 0;
	
	if (size > getpagesize())
		map_size = (((size + META_BLOCK_SIZE + META_MAP_SIZE - 1) /
					page_size + 1) * page_size);
	else
		map_size = ((((size + META_BLOCK_SIZE) * 100 + META_MAP_SIZE - 1) /
				page_size + 1) * page_size);

	if ((map = mmap(NULL, map_size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	
	// init g_type list if not exist else list is updated in select_map
	if (g_types_tab[type] == NULL)
		g_types_tab[type] = map;

	init_map(&map, (map_size - ALIGN_4(sizeof(t_map))), map_size);	
	
	return map;	
}

static void     init_map(t_map **node, size_t size, size_t mapsize)
{
	(*node)->next = NULL;
	(*node)->free_space = mapsize - 100 * META_BLOCK_SIZE - META_MAP_SIZE
	(*node)->block = init_block(size, *node);
}


/*
** get map that fits size or create a new one
** @return map to work on.
*/

t_map		    *get_map(int type, size_t size)
{
	return ((g_types_tab[type]) ?
			select_map(&g_types_tab[type], size, type) :
			create_map(get_size(size), type));
}