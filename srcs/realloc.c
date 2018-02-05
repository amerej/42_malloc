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

	ft_putstr("\nf(update_malloc)");
	if (oldtype == LARGE && size > 512 && size <= block->size + (*map)->free_space)
	{ /* means new large, even smaller/larger than oldsize, fits in the map */
		ft_putstr("\nf(if LARGE and smaller/larger but still fits) edit block");
		(*map)->free_space += block->size - size;
		block->size = size;
		block->next = create_block((*map), (*map)->free_space, block, NULL);
	}
	else if (oldtype == LARGE || oldtype != newtype)
	{ /* means full realloc of a LARGE that doesnt fit 1st condi OR newsize doesn't is of a different type than oldsize */
		ft_putstr("\nf(if block->size < size). free& malloc, snewize :");
		ft_putnbr_base((long)size, 10);
		ft_putstr(" oldsize :");
		ft_putnbr_base((long)block->size, 10);
		new_ptr = malloc(size);
		new_ptr = ft_memcpy(new_ptr, block->ptr, (block->size > size) ? block->size : size);
		free(block->ptr);
		return (new_ptr);
	}
    else // if (block->size >= size)
	{
		ft_putstr("\nelse just dont change a thing");
		return (block->ptr);
	}
}

static void		*browse_found_map(t_map **map, t_block *to_realloc, size_t size)
{
	t_block		*block;

	ft_putstr("\nf(browse_map)");

	block = (*map)->block; // NO MAPS BLOCK
	while (block)
	{
		if (block == to_realloc) // NE RENTRE PAS DANS LA CDT
			return update_malloc(map, block, size);
		block = block->next;
	}
	ft_putstr("\nBM ::: END\n");
    return NULL;
}

static void		*find_map(t_map **map, void *ptr, size_t size, int page)
{
	ft_putstr("\nf(find_map)");
	int		maptype;
	
	maptype = get_type((*map)->block->size);
  	if ((long)((void*)*map + getpagesize() * page) == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
  	{
		ft_putstr("\nMap found");
		return browse_found_map(map, ptr - BLOCK_SIZE, size);
	}
	else if (maptype != LARGE && (*map)->page_count > (size_t)page)
	{
		ft_putstr("\npage->count "); ft_putnbr_base((long)(*map)->page_count, 10);
		return find_map(map, ptr, size, page + 1);
	}
	else if ((*map)->next)
	{
		ft_putstr(" map->next");
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
	// show_alloc_mem();

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
			ft_putstr("\nglobal "); ft_putnbr_base((long)&g_types_tab[type], 16);
			ft_putstr(" type "); ft_putnbr_base((long)type, 10);
			if ((realloced_ptr = find_map(&g_types_tab[type], ptr, size, 0)))
			{
				// show_alloc_mem();
				return realloced_ptr;
			}
		}
		type++;
	}
	// show_alloc_mem();

	ft_putstr("\nf(realloc) NOTHING FOUND: ");ft_putnbr_base((long)ptr, 16);	
    return ptr;
}