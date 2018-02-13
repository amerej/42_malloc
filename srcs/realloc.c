/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 15:01:01 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*ft_memcpy(void *dst, const void *src, size_t len)
{
	char	*str_dst;
	char	*str_src;
	size_t	count;

	str_dst = (char *)dst;
	str_src = (char *)src;
	count = 0;
	while (count < len)
	{
		str_dst[count] = str_src[count];
		count++;
	}
	return (dst);
}

static void		*update_malloc(t_map **map, t_block *block, size_t size)
{
	void	*new_ptr;
	int		oldtype;

	new_ptr = NULL;
	oldtype = get_type(block->size);
	if (oldtype == LARGE && size > 512
		&& size <= block->size + (*map)->free_space)
	{
		(*map)->free_space += block->size - size;
		block->size = size;
		block->next = create_block((*map), (*map)->free_space, block, NULL);
	}
	else if (oldtype == LARGE || oldtype != get_type(size))
	{
		new_ptr = ts_malloc(size);
		if (new_ptr != NULL)
			ft_memcpy(new_ptr, block->ptr,
				block->size < size ? block->size : size);
		else
			exit(1);
		ts_free(block->ptr);
		return (new_ptr);
	}
	return (block->ptr);
}

static void		*browse_found_map(t_map **map, t_block *to_realloc, size_t size)
{
	t_block		*block;

	block = (*map)->block;
	while (block)
	{
		if (block == to_realloc)
			return (update_malloc(map, block, size));
		block = block->next;
	}
	return (NULL);
}

static void		*find_map(t_map **map, void *ptr, size_t size, int page)
{
	int		maptype;
	void	*cur_page_addr;

	maptype = (*map)->type;
	cur_page_addr = (void*)*map + getpagesize() * page;
	if ((long)cur_page_addr == ((long)ptr & 0xFFFFFFFFF000))
	{
		return (browse_found_map(map, ptr - BLOCK_SIZE, size));
	}
	else if (maptype != LARGE && (*map)->page_count > (size_t)page - 1)
	{
		return (find_map(map, ptr, size, page + 1));
	}
	else if ((*map)->next)
	{
		return (find_map(&(*map)->next, ptr, size, 0));
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	int		type;
	void	*reallocated_ptr;

	ft_putstr("\nf(realloc), ptr: ");
	ft_putnbr_base((long)ptr, 16);
	ft_putstr(" , size : ");
	ft_putnbr_base((long)size, 10);
	type = 0;
	reallocated_ptr = NULL;
	if (ptr == NULL)
		return (ts_malloc(size));
	if (size == 0)
	{
		ts_free(ptr);
		return (NULL);
	}
	size = get_size(size);
	while (type < MAX_TYPE)
	{
		if (g_types_tab[type])
		{
			if ((reallocated_ptr = find_map(&g_types_tab[type], ptr, size, 0)))
			{
				ft_putstr("\nf(realloc) RETURN: ");
				ft_putnbr_base((long)reallocated_ptr, 16);
				return (reallocated_ptr);
			}
		}
		type++;
	}
	ft_putstr("\nf(realloc) NOTHING FOUND: ");
	ft_putnbr_base((long)ptr, 16);
	return (NULL);
}
