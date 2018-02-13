/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:12:44 by gwojda            #+#    #+#             */
/*   Updated: 2017/11/07 15:00:35 by gwojda           ###   ########.fr       */
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

void		m_show_alloc_mem_ex(void)
{
	t_stack *list;

	list = g_lst;
	while (list)
	{
		if (!list->free)
		{
			ft_putstr("list content :\n");
			print_hexa((char *)list, sizeof(*list));
			ft_putstr("map content :\n");
			print_hexa((char *)list->ptr, list->size);
		}
		list = list->next;
	}
}

void		show_alloc_mem_ex(void)
{
	pthread_mutex_lock(&g_mutex);
	m_show_alloc_mem_ex();
	pthread_mutex_unlock(&g_mutex);
}
