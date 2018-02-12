#include "../includes/malloc.h"

static void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char	*str_dst;
	char	*str_src;
	size_t	count;

	str_dst = (char *)dst;
	str_src = (char *)src;
	count = 0;
	while (count < len)
	{
		str_dst[count] = str_src[count];
		count++;
	}
	return (dst);
}

static void		*update_malloc(t_map **map, t_block *block, size_t size)
{
	void	*new_ptr;
	int		oldtype;
	int		newtype;

	new_ptr = NULL;
	oldtype = get_type(block->size);
	newtype = get_type(size);

	if (oldtype == LARGE && size > 512 && size <= block->size + (*map)->free_space)
	{ /* means new large, even smaller/larger than oldsize, fits in the map */
		(*map)->free_space += block->size - size;
		block->size = size;
		block->next = create_block((*map), (*map)->free_space, block, NULL);
	}
	else if (oldtype == LARGE || oldtype != newtype)
	{ /* means full realloc of a LARGE that doesnt fit 1st condi OR newsize doesn't is of a different type than oldsize */
		new_ptr = malloc(size);
		if (new_ptr != NULL)
			ft_memcpy(new_ptr, block->ptr, (block->size < size) ? block->size : size);
		else
			exit(1);
		free(block->ptr);
		return (new_ptr);
	}
	return (block->ptr);
}

static void		*browse_found_map(t_map **map, t_block *to_realloc, size_t size)
{
	t_block		*block;

	block = (*map)->block; // NO MAPS BLOCK
	while (block)
	{
		if (block == to_realloc) // NE RENTRE PAS DANS LA CDT
			return update_malloc(map, block, size);
		block = block->next;
	}
    return NULL;
}

static void		*find_map(t_map **map, void *ptr, size_t size, int page)
{
	int		maptype;
	
	maptype = (*map)->type;
  	if ((long)((void*)*map + getpagesize() * page) == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
  	{
		return browse_found_map(map, ptr - BLOCK_SIZE, size);
	}
	else if (maptype != LARGE && (*map)->page_count > (size_t)page - 1)
	{
		return find_map(map, ptr, size, page + 1);
	}
	else if ((*map)->next)
	{
		return find_map(&(*map)->next, ptr, size, 0);
	}
	return NULL;
}

void			*realloc(void *ptr, size_t size)
{
	int		type;
    void    *realloced_ptr;
	ft_putstr("\nf(realloc), ptr: ");ft_putnbr_base((long)ptr, 16);
	ft_putstr(" , size : ");ft_putnbr_base((long)size, 10);	

	type = 0;
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	size = get_size(size);
	while (type < MAX_TYPE)
	{
		if (g_types_tab[type]) {
			if ((realloced_ptr = find_map(&g_types_tab[type], ptr, size, 0)))
			{
				ft_putstr("\nf(realloc) RETURN: "); ft_putnbr_base((long)realloced_ptr, 16);					
				return realloced_ptr;
			}
		}
		type++;
	}

	ft_putstr("\nf(realloc) NOTHING FOUND: "); ft_putnbr_base((long)ptr, 16);	
    return ptr;
}