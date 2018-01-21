#include "../includes/malloc.h"

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
	int i = 0;
	int	random = 0;
	ft_putstr(">>> MAIN TEST <<<\n");	
	// while (i < 5)
	// {
	// 	random = 5; //rand();
	// 	str = (char *)malloc(random);

	// 	ft_strlcpy(str, random);
		
	// 	ft_putstr("\nSTR VALUE AFTER MALLOC (");
	// 	ft_putnbr(random);
	// 	ft_putstr(") ->>>>>>>>>>>>> ");
	// 	ft_putstr(str);
	// 	ft_putstr("\n");

	// 	free(str);
		
	// 	++i;
	// }

	// char *str1 = (char*)malloc(1);
	// char *str2 = (char*)malloc(2);
	// char *str3 = (char*)malloc(3);
	// char *str4 = (char*)malloc(4);
	// char *str5 = (char*)malloc(5);
	// char *str6 = (char*)malloc(6);
	char *str10 = (char*)malloc(4097);
	char *str11 = (char*)malloc(3913);			
	// char *str12 = (char*)malloc(4099);
	// char *str13 = (char*)malloc(40911232);	
	// char *str14 = (char*)malloc(40129214);	
	// char *str15 = (char*)malloc(40291215);	
	
	ft_putstr("\nDONE MALLOCING\n");

	show_alloc_mem();
	
	free(str10); //show_alloc_mem();
	free(str11); //show_alloc_mem();
	// free(str6); //show_alloc_mem();
	// free(str4);	//show_alloc_mem();
	// free(str2); //show_alloc_mem();
	// free(str3); //show_alloc_mem();
	// free(str1); //show_alloc_mem();
	// free(str5); //show_alloc_mem();
	// free(str12); //show_alloc_mem();
	// free(str13); //show_alloc_mem();
	// free(str14); //show_alloc_mem();
	// free(str15);
	show_alloc_mem();

	ft_putstr("\nFREE ALL DONE\n");
}


BUGS LIST ::
APPLY PAGES_COUNT to free LARGE on several pages
CHECK THE UNMAP MAP MANIPULATIONS