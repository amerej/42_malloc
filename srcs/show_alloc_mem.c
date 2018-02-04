/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/04 16:39:58 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_blocks(t_block *block)
{
	ft_putstr("\t\tH: 0x");			
	ft_putnbr_base((long)block, 16);
	ft_putstr(" => B: 0x");
	ft_putnbr_base((long)block->ptr, 16);
	ft_putstr(" - 0x");
	ft_putnbr_base((long)(block->ptr + block->size), 16);
	ft_putstr(" : ");
	ft_putnbr_base(block->size, 10);
	ft_putstr(" octets, ");
	(block->free) ? ft_putstr("free: TRUE\n") : ft_putstr("free: FALSE\n");
	if (block->next)
		print_blocks(block->next);
}

static void		print_maps(t_map *map, size_t count)
{
	ft_putstr("\tmap");
	ft_putnbr_base((long)count, 10);
	ft_putstr(" - addr: ");
	ft_putnbr_base((long)map, 16);	
	ft_putstr("\n");
	if (map->block)
		print_blocks(map->block);
	else
		ft_putstr("THERE MUST BE AN ERROR: NO EXISTING BLOCKS IN MAP\n");
	if (map->next)
		print_maps(map->next, ++count);
}

static t_bool	print_header(t_map *head, char *str_type)
{
	if (!head)
	{
		ft_putstr(str_type);
		ft_putstr(" : NULL, no allocated map\n");
		return FALSE;
	}
	ft_putstr(str_type);
	ft_putstr(": 0x");
	ft_putnbr_base((long)head, 16);
	ft_putstr("\n");
	return TRUE;
}

static void	print_alloc_mem_type(int type, char *str_type)
{
	if (!print_header(g_types_tab[type], str_type))
		return;
	print_maps(g_types_tab[type], 0);
}

void		print()
{
	int		type;
	t_map	*map;
	t_block	*block;
	t_map	*eta;

	type = 0;
	while (type < MAX_TYPE)
	{
		ft_putstr("\ntype: ");
		ft_putnbr_base((long)type, 10);
		if ((map = g_types_tab[type])) {
			while (map)
			{
				block = map->block;
				eta = (void*)map + getpagesize() * map->page_count;
				ft_putstr("\neta:   "); ft_putnbr_base((long)eta, 16);
				while (block)// && block < eta)
				{
					ft_putstr("\nblock: "); ft_putnbr_base((long)block, 16);
					block = block->next;
				}
				map = map->next;
			}
		}
		type++;
	}
}

void		show_alloc_mem(void)
{
	// return;
	// print();	
	ft_putstr("\n");
	print_alloc_mem_type(TINY, "TINY");
	ft_putstr("\n");	
	print_alloc_mem_type(SMALL, "SMALL");
	ft_putstr("\n");
	print_alloc_mem_type(LARGE, "LARGE");
}