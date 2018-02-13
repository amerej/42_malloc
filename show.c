/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:12:44 by gwojda            #+#    #+#             */
/*   Updated: 2017/11/07 15:02:13 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		put_memory_maj(unsigned int nb)
{
	char	*str;

	str = "0123456789ABCDEF";
	if (nb % 16 != nb)
		put_memory_maj(nb / 16);
	ft_putchar(str[nb % 16]);
}

static void	print_header(t_stack *list)
{
	if (list->type == IS_TINY)
	{
		ft_putstr("TINY : 0x");
		put_memory_maj((unsigned int)list);
		ft_putstr("\n");
	}
	else if (list->type == IS_SMALL)
	{
		ft_putstr("SMALL : 0x");
		put_memory_maj((unsigned int)list);
		ft_putstr("\n");
	}
	else if (list->type == IS_LARGE)
	{
		ft_putstr("LARGE : 0x");
		put_memory_maj((unsigned int)list);
		ft_putstr("\n");
	}
}

static void	print_line(t_stack *list)
{
	ft_putstr("0x");
	put_memory_maj((unsigned int)list);
	ft_putstr(" - 0x");
	put_memory_maj((unsigned int)list->ptr);
	ft_putstr(" - 0x");
	put_memory_maj((unsigned int)list->ptr + list->size);
	ft_putstr(WHITE);
	ft_putstr(" : ");
	ft_putnbr(list->size);
	ft_putstr(" octets\n");
}

static void	show_alloc_mem_type(char type, size_t *total, size_t *lost)
{
	t_stack *list;

	list = g_lst;
	while (list)
	{
		if (list->ref_page && list->type == type)
			print_header(list);
		if (list->type == type && !list->free)
		{
			ft_putstr(RED);
			print_line(list);
			*total += list->size;
		}
		else if (list->type == type && list->free)
		{
			ft_putstr(GREEN);
			print_line(list);
		}
		*lost += sizeof(list);
		list = list->next;
	}
}

void		show_alloc_mem(void)
{
	t_stack *list;
	size_t	total;
	size_t	lost;

	lost = 0;
	total = 0;
	list = g_lst;
	show_alloc_mem_type(IS_TINY, &total, &lost);
	show_alloc_mem_type(IS_SMALL, &total, &lost);
	show_alloc_mem_type(IS_LARGE, &total, &lost);
	ft_putstr("Lost : ");
	ft_putnbr(lost);
	ft_putstr(" octets\n");
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}
