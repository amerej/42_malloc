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

void		put_memory_maj_off(unsigned int nb, int nbr)
{
	char	*str;

	str = "0123456789ABCDEF";
	if (nbr > 0)
		put_memory_maj_off(nb / 16, --nbr);
	ft_putchar(str[nb % 16]);
}

static void	print_hexa(char *ptr, size_t size)
{
	size_t	i;

	i = 1;
	while (i <= size)
	{
		put_memory_maj_off(ptr[i], 1);
		if (!(i % 16))
			ft_putchar('\n');
		else
			ft_putchar(' ');
		++i; 
	}
	ft_putchar('\n');
}

static void		print_block_content(t_block *block)
{
	print_hex((char *)list->ptr, list->size);
}

static void		print_block_addr(t_block *block)
{
	ft_putstr("\t\tBLOCK : 0x");
	ft_putnbr_base((long)block->ptr, 16);
	ft_putstr(" - 0x");
	ft_putnbr_base((long)(block->ptr + block->size), 16);
	ft_putstr(" : ");
	ft_putnbr_base(block->size, 10);
	ft_putstr(" octets");
	(block->free) ? ft_putstr("free: TRUE\n") : ft_putstr("free: FALSE\n");
	print_block_content(block);
	if (block->next)
		print_block_addr(block->next);
}

static void		print_maps(t_map *map, size_t count)
{
	ft_putstr("\tMAP : ");
	ft_putnbr_base((long)count, 10);
	ft_putstr(" - addr : ");
	ft_putnbr_base((long)map, 16);
	ft_putstr("\n");
	if (map->block)
		print_blocks(map->block);
	if (map->next)
		print_maps(map->next, ++count);
}

static t_bool	print_header(t_map *head, char *str_type)
{
	if (!head)
	{
		ft_putstr(str_type);
		ft_putstr(" : NULL, no allocated map\n");
		return (FALSE);
	}
	ft_putstr(str_type);
	ft_putstr(": 0x");
	ft_putnbr_base((long)head, 16);
	ft_putstr("\n");
	return (TRUE);
}

static void		print_alloc_mem_type(int type, char *str_type)
{
	if (!print_header(g_types_tab[type], str_type))
		return ;
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
