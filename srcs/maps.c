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

static void     init_map(t_map **map, size_t size, size_t mapsize)
{
	(*map)->free_space = mapsize - META_MAP_SIZE
	(*map)->block = create_block(map, size);
	(*map)->block->next = create_block(map, (*map)->free_space)

	(*map)->next = NULL;
}

static t_map		*create_map(int type, size_t size)
{
	t_map	*map;

	size_t	map_size;

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
	
	if (size > getpagesize())
		map_size = (((size + META_BLOCK_SIZE + META_MAP_SIZE - 1) /
					page_size + 1) * page_size);
	else
		map_size = ((((size + META_BLOCK_SIZE) * 100 + META_MAP_SIZE - 1) /
				page_size + 1) * page_size);

	if ((map = mmap(NULL, map_size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	
	// init g_type list if not exist else list is updated in get_block
	if (g_types_tab[type] == NULL)
		g_types_tab[type] = map;

	init_map(&map, (map_size - ALIGN_4(sizeof(t_map))), map_size);	
	
	return map;	
}

/*
** get map that fits size or create a new one
** @return map to work on.
*/

t_map		    *get_map_list(int type, size_t size)
{
	return ((g_types_tab[type]) ?
			g_types_tab[type] :
			create_map(type, size));
}