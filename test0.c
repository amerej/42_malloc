#include "includes/malloc.h"
#include <string.h>
#define M (1024 * 1024) 

int main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 100)
	{
		addr = (char*)malloc(16); 
		addr[0] = 42;
		i++;
	}
	show_alloc_mem();
	return (0); 
}