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

/*
** TYPEOF(t_map) defined in malloc.h as an extern variable
** 3 types_tab elems : one for TINY / SMALL / LARGE
** each types_tab elem contains a list of mmap results (t_block)
*/

g_types_tab = {NULL, NULL, NULL};

void	move_to_allocable_space(t_map *node)
{
	t_map *lst;

	lst = (void *)node + META_MAP_SIZE;

}

void	*malloc(size_t size)
{
	t_map 	*map_list;
	t_block	*block;
	int		type;

	if (size <= 0)
		return (NULL); // check expected return	

	type = get_type(size);
	
	map_list = get_map_list(type, size); // get the right map to work on
	if (!map_lst)
		return (NULL);

	block = get_block(map_list, type, size);

	// move_to_allocable_space(map_lst);
}
