/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 15:01:01 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			*ts_reallocf(void *ptr, size_t size)
{
	void	*reallocated_ptr;

	ft_putstr("\nf(reallocf), ptr: ");
	ft_putnbr_base((long)ptr, 16);
	ft_putstr(" , size : ");
	ft_putnbr_base((long)size, 10);
	if (size == 0)
	{
		ts_free(ptr);
		return (NULL);
	}
	else if ((reallocated_ptr = ts_realloc(ptr, size)))
		ts_free(ptr);
	return (reallocated_ptr);
}
