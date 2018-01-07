#include "../includes/malloc.h"

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

int main (int argc, char** argv)
{
	char *str;
	char *str2;

	str = (char *)malloc(7);
	str = "coucou";
	ft_putstr("\n");
	ft_putstr(str);
	ft_putstr("\n&addr str allouée par malloc: ");
	ft_putnbr_hex((size_t)str);
	ft_putstr("\n");

	str2 = (char *)malloc(12);
	str2 = "YO BRO CA VA?";
	ft_putstr("\n");
	ft_putstr(str2);
	ft_putstr("\n&addr str allouée par malloc: ");
	ft_putnbr_hex((size_t)str2);
	ft_putstr("\n");

}