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

	char *str1 = (char*)malloc(1);
	char *str2 = (char*)malloc(22);
	char *str3 = (char*)malloc(323);
	char *str4 = (char*)malloc(4);
	char *str5 = (char*)malloc(53);
	char *str6 = (char*)malloc(16);
	char *str7 = (char*)malloc(716);	
	char *str10 = (char*)malloc(4097);
	char *str15 = (char*)malloc(4023423421);	
	char *str14 = (char*)malloc(40914);	
	char *str16 = (char*)malloc(3005);
	char *str11 = (char*)malloc(36700093186723);			
	char *str12 = (char*)malloc(454523594);
	char *str13 = (char*)malloc(40923423212);	
	char *str17 = (char*)malloc(3000);		
	char *str18 = (char*)malloc(3100);		
	char *str19 = (char*)malloc(3200);		
	
	ft_putstr("\nDONE MALLOCING\n");

	show_alloc_mem();
	
	// free(str15);
	// free(str19);	
	// free(str14); //show_alloc_mem();
	// free(str16);
	// free(str11); //show_alloc_mem();
	// free(str13); //show_alloc_mem();
	// free(str12); //show_alloc_mem();
	// free(str10); //show_alloc_mem();
	// free(str1); //show_alloc_mem();
	// free(str2); //show_alloc_mem();
	// free(str3); //show_alloc_mem();
	// free(str4);	//show_alloc_mem();
	// free(str5); //show_alloc_mem();
	// free(str6); //show_alloc_mem();
	// free(str17); //show_alloc_mem();
	// free(str18); //show_alloc_mem();
	// free(str19);
	ft_putstr("\nDONE FREEING\n");
	show_alloc_mem();
}


// BUGS LIST ::
// CHECK THE UNMAP MAP MANIPULATIONS