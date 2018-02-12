/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:49:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/11 19:18:08 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int			get_type(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	else if (size <= SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}

size_t		get_size(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY_SIZE);
	else if (size <= SMALL_SIZE)
		return (SMALL_SIZE);
	else
		return (size);
}

void		ft_putchar(char c)
{
	// return ;
	write(2, &c, 1);
}

void	ft_putstr(char *str)
{
	// return;
	size_t i;
	
	i = 0;
	while (str[i])
		++i;
	write(2, str, i);
}

void	ft_putnbr_base(long nb, int base)
{
	// return;
	char	*str;

	str = "0123456789ABCDEF";
	if (nb % base != nb)
		ft_putnbr_base(nb / base, base);
	ft_putchar(str[nb % base]);
}