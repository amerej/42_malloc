/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:49:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/01/06 18:58:02 by gpoblon          ###   ########.fr       */
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

int			get_size(size_t size)
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
	write(1, &c, 1);
}

static void	ft_putnbr_loop(long n, int base)
{
	if (n >= base)
		ft_putnbr_loop(n / base, base);
	ft_putchar("0123456789abcdef"[n % base]);
}

void		ft_putnbr_hex(long n)
{
	ft_putstr("0x");
	ft_putnbr_loop(n, 16);
}

void	ft_putnbr(long n)
{
	if (n < 0)
		ft_putstr("-");
	n = (n > 0 ? n : -n);
	ft_putnbr_loop(n, 10);
}

void	ft_putstr(char *str)
{
	size_t i;
	
	i = 0;
	while (str[i])
		++i;
	write(1, str, i);
}