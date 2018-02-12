#include "../includes/malloc.h"

static void		ft_bzero(void *s, size_t n)
{
	while (n--)
		((t_uchar*)s)[n] = '\0';
}

void			*calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, get_size(count * size));
	return (ptr);
}