#include "includes/malloc.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

# define SIZE 	1500

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

/*
** 16 small malloc realloc free
** 17 big malloc realloc free
** 19 thousand small realloc free
** 20 ten big malloc realloc free
*/

int main (void)
{
	char *str1 = (char*)malloc(1500);
	str1 = realloc(str1, 1500);
	free(str1);
}
