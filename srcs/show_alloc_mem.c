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

static void		print_blocks(t_block *block)
{
	ft_putstr("H: 0x");			
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

static void		print_maps(t_map *map)
{
	if (map->block)
		print_blocks(map->block);
	else
		ft_putstr("THERE MUST BE AN ERROR: NO EXISTING BLOCKS IN MAP\n");	
	if (map->next)
		print_maps(map->next);
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
	print_maps(g_types_tab[type]);
}

void		show_alloc_mem(void)
{
	ft_putstr("\n");	
	print_alloc_mem_type(TINY, "TINY");
	ft_putstr("\n");	
	print_alloc_mem_type(SMALL, "SMALL");
	ft_putstr("\n");
	print_alloc_mem_type(LARGE, "LARGE");
}