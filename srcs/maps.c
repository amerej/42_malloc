/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 15:06:05 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void     init_map(t_map **map, size_t mapsize, t_map *prevmap)
{
	ft_putstr("\nf(init_map)");

	(*map)->free_space = mapsize - MAP_SIZE - BLOCK_SIZE; // BLOCK_SIZE added to prevent segf
	(*map)->page_count = mapsize / getpagesize();	
	(*map)->block =
		create_block(*map, (*map)->free_space, NULL, NULL);
	(*map)->next = NULL;
	(*map)->prev = prevmap;
}

t_map			*create_map(int type, size_t size, t_map *prevmap)
{
	t_map	*map;
	size_t	psize;
	size_t	mapsize;

	map = NULL;
	ft_putstr("\nf(create_map)");
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
	
	psize = (size_t)getpagesize();

	mapsize = (size > SMALL_SIZE) ?
		((size + BLOCK_SIZE * 2 + MAP_SIZE - 1) / psize + 1) * psize :
		(((size + BLOCK_SIZE) * 100 + MAP_SIZE - 1) / psize + 1) * psize;

	if ((map = mmap(NULL, mapsize, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED) {
			ft_putstr("\nMAP FAILED\n");
			return (NULL);
		}

	// ft_putstr(" g_types_large: "); ft_putnbr_base((long)map, 16);
	
	init_map(&map, mapsize, prevmap);
	// init g_type list if not exist else list is updated in get_block
	if (g_types_tab[type] == NULL)
		g_types_tab[type] = map;

	if (g_types_tab[type])
		g_types_tab[type]->last = map;

	return map;
}

/*
** get map that fits size or create a new one
** @return map to work on.
*/

t_map		    *get_map_lst(int type, size_t size)
{
	ft_putstr("\nf(get_map_lst)");
	ft_putstr(" type: "); ft_putnbr_base((long)type, 10);

	
	if (type == LARGE && g_types_tab[LARGE])
	{
		ft_putstr(" g_types_large: "); ft_putnbr_base((long)g_types_tab[LARGE]->last, 16);
		return g_types_tab[LARGE]->last;
	}
	return ((g_types_tab[type]) ?
		g_types_tab[type] :
		create_map(type, size, NULL));
}