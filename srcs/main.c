#include "../includes/malloc.h"

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

int main()
{
int i;
char *addr;

i = 0;
while (i < 1024)
{
	addr = (char*)malloc(1024); 
	addr[0] = 42; 
	free(addr);
	i++;
}
return (0); 
}

// int main (int argc, char** argv)
// {
// 	ft_putstr(">>> MAIN TEST <<<\n");	
// 	// int i = 0;
// 	// char	**tab[55001];
// 	// size_t	random = 0;
// 	// while (i < 3)
// 	// {
// 	// 	random = rand();
		
// 	// 	tab[i] = (char *)malloc(random);
		
// 	// 	// show_alloc_mem();
// 	// 	++i;
// 	// }

// 	// ft_putstr("\n\nfree 1"); free(str1); //show_alloc_mem();
// 	// char *str2 = (char*)malloc(952);
// 	// char *str3 = (char*)malloc(776);
// 	// ft_putstr("\n\nfree 2"); free(str2); //show_alloc_mem();
// 	// char *str4 = (char*)malloc(952);
// 	// char *str5 = (char*)malloc(19200);
// 	// ft_putstr("\n\nfree 4"); free(str4);	//show_alloc_mem();
// 	// char *str6 = (char*)malloc(768);
// 	// ft_putstr("\n\nfree 6"); free(str6); //show_alloc_mem();
// 	// ft_putstr("\n\nfree 7"); free(str7);	//show_alloc_mem();
// 	// char *str11 = (char*)malloc(36700093186723);			
// 	// ft_putstr("\n\nfree 5"); free(str5); //show_alloc_mem();
// 	// ft_putstr("\n\nfree 11"); free(str11); //show_alloc_mem();
// 	// char *str12 = (char*)malloc(454523594);
// 	// char *str13 = (char*)malloc(40923423212);	
// 	// char *str14 = (char*)malloc(40914);	
// 	// ft_putstr("\n\nfree 13"); free(str13); //show_alloc_mem();
// 	// ft_putstr("\n\nfree 3"); free(str3); //show_alloc_mem();
// 	// char *str15 = (char*)malloc(4023423421);	
// 	// char *str16 = (char*)malloc(0);
// 	// ft_putstr("\n\nfree 15"); free(str15);
// 	// ft_putstr("\n\nfree 16"); free(str16);
// 	// ft_putstr("\n\nfree 12"); free(str12); //show_alloc_mem();
// 	// char *str17 = (char*)malloc(768);
// 	// char *small = (char*)malloc(17);
// 	// char *tiny = (char*)malloc(16);
	
// 	char *str1 = (char*)malloc(1);  ft_strlcpy(str1, 15, '1'); ft_putstr(str1);
// 	char *str2 = (char*)malloc(7);	 ft_strlcpy(str2, 15, '2'); ft_putstr(str2);
// 	char *str3 = (char*)malloc(10); ft_strlcpy(str3, 15, '3'); ft_putstr(str3);
	
// 	ft_putstr("\nDONE MALLOCING\n");

// 	show_alloc_mem();

// 	// str2 = (char*)realloc(str2, 1);			
	
// 	// ft_putstr("\nDONE REALLOCING\n");


// 	// show_alloc_mem();
	
// 	// ft_putstr("\n\nfree 1"); free(str1); //show_alloc_mem();
// 	// ft_putstr("\n\nfree 2"); free(str2); //show_alloc_mem();
// 	// ft_putstr("\n\nfree 10"); free(str10); //show_alloc_mem();
	
// 	// show_alloc_mem();
// 	// str2 = (char*)malloc(7); ft_strlcpy(str2, 15, '2');
// 	;//show_alloc_mem();	

// 	ft_putstr("\n\nfree 1"); free(str1); //show_alloc_mem();
// 	ft_putstr("\n\nfree 2"); free(str2); //show_alloc_mem();
// 	ft_putstr("\n\nfree 3"); free(str3); //show_alloc_mem();


// 	// ft_putstr("\n\nfree 14"); free(str14); //show_alloc_mem();
// 	// ft_putstr("\n\nfree 17"); free(str17); //show_alloc_mem();
// 	// ft_putstr("\n\nfree tiny"); free(tiny);
// 	// ft_putstr("\n\nfree small"); free(small);

// 	// while (i >= 0)
// 	// {
// 	// 	free(tab[i]);
// 	// 	--i;
// 	// }

// 	show_alloc_mem();
	
// 	ft_putstr("\nDONE FREEING\n");	
// }


// // BUGS LIST ::
// // CHECK THE UNMAP MAP MANIPULATIONS