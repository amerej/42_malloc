/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/07 03:06:16 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_maps_and_blocks(t_map *map)
{
	t_block	*block;
	if (map)
	{
		block = map->block;
		while (block)
		{
			ft_putstr("H: 0x");			
			ft_putnbr_base((long)block, 16);
			ft_putstr(" => B: 0x");
			ft_putnbr_base((long)block->ptr, 16);
			ft_putstr(" - 0x");
			ft_putnbr_base((long)(block->ptr + block->size), 16);
			ft_putstr(" : ");
			ft_putnbr_base(block->size, 10);
			ft_putstr(" octets\n");
			block = block->next;
		}
	}
	if (map->next)
		print_maps_and_blocks(map->next);
}

static void	print_alloc_mem_type(int type, char *str_type)
{
	/*
	**	print header
	*/
	if (!g_types_tab[type])
	{
		ft_putstr(str_type);
		ft_putstr(" : NULL, no allocated map\n");
		return;
	}
	ft_putstr(str_type);
	ft_putstr(": 0x");
	ft_putnbr_base((long)g_types_tab[type], 16);
	ft_putstr("\n");

	/*
	**	print body: maps and blocks
	**	just keep last line, if/else = debug
	*/
	if (!(g_types_tab[type])->block)
		ft_putstr("THERE MUST BE AN ERROR: NO EXISTING BLOCKS\n");
	else
		print_maps_and_blocks(g_types_tab[type]);
}

void		show_alloc_mem(void)
{
	print_alloc_mem_type(TINY, "TINY");
	ft_putstr("\n");	
	print_alloc_mem_type(SMALL, "SMALL");
	ft_putstr("\n");	
	print_alloc_mem_type(LARGE, "LARGE");
}