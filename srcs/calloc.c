/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 15:01:01 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
		*(char *)s++ = 0;
}

void			*ts_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (!count)
		count = 1;
	if (!size)
		size = 1;
	if ((ptr = ts_malloc(count * size)))
		ft_bzero(ptr, get_size(count * size));
	return (ptr);
}
