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

void	ft_strlcpy(char *str, int len)
{
	int		i = 0;

	while (i < len)
	{
		str[i] = 'a';
		i++;
	}
	str[i] = '\0';
}

int main (int argc, char** argv)
{
	char *str;

	int i = 0;
	int	random = 0;
	ft_putstr(">>> MAIN <<<");	
	while (i < 5)
	{
		random = 5; //rand();
		str = (char *)malloc(random);

		ft_strlcpy(str, random);
		
		ft_putstr("\nSTR VALUE AFTER MALLOC (");
		ft_putnbr(random);
		ft_putstr(") ->>>>>>>>>>>>> ");
		ft_putstr(str);
		ft_putstr("\n");

		free(str);
		
		++i;
	}
}