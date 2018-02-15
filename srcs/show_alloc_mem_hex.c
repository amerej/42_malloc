/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/14 13:04:42 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_hexa(char *ptr, size_t size)
{
	size_t	i;
	char	*str;
	unsigned char	nb;

	i = 0;
	str = "0123456789ABCDEF";
	nb = 0;
	while (++i <= size)
	{
		nb = ptr[i];
		ft_putchar(str[nb % 16]);
		ft_putchar(str[(nb / 16) % 16]);
		if (i % 16)
			ft_putchar(' ');
		else
			ft_putchar('\n');
	}
	ft_putchar('\n');
}

static void		print_block_addr(t_block *block)
{
	ft_putstr("\nBLOCK : 0x");
	ft_putnbr_base((long)block->ptr, 16);
	ft_putstr(" - 0x");
	ft_putnbr_base((long)(block->ptr + block->size), 16);
	ft_putstr(" : ");
	ft_putnbr_base(block->size, 10);
	ft_putstr(" octets - ");
	(block->free) ? ft_putstr("FREE\n") : ft_putstr("ALLOCATED\n");
	print_hexa((char *)block->ptr, block->size);
	if (block->next)
		print_block_addr(block->next);
}

static void		print_maps(t_map *map, size_t count)
{
	ft_putstr("\nMAP : ");
	ft_putnbr_base((long)count, 10);
	ft_putstr(" - addr : ");
	ft_putnbr_base((long)map, 16);
	ft_putstr("\n");
	if (map->block)
		print_block_addr(map->block);
	if (map->next)
		print_maps(map->next, ++count);
}

static void		print_alloc_mem_type(int type, char *str_type)
{
	if (!g_types_tab[type])
	{
		ft_putstr(str_type);
		ft_putstr(" : NULL, no allocated map\n");
		return ;
	}
	ft_putstr(str_type);
	ft_putstr(": 0x");
	ft_putnbr_base((long)g_types_tab[type], 16);
	ft_putstr("\n");
	print_maps(g_types_tab[type], 0);
}

void			show_alloc_mem_hex(void)
{
	ft_putstr("\n");
	print_alloc_mem_type(TINY, "TINY");
	ft_putstr("\n");
	print_alloc_mem_type(SMALL, "SMALL");
	ft_putstr("\n");
	print_alloc_mem_type(LARGE, "LARGE");
}
