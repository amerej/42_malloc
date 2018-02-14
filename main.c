#include "includes/malloc.h"

void	ft_strlcpy(char *str, int len, char c)
{
	int		i = 0;

	while (i < len)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
}

int main (int argc, char** argv)
{
	char *str1 = (char*)malloc(1);
	char *str2 = (char*)malloc(7);
	char *str3 = (char*)malloc(10);
	show_alloc_mem_hex();
	free(str1);
	free(str2);
	free(str3);
}
