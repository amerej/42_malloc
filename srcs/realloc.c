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

static void		*update_malloc(t_block *block, size_t size)
{
	void	*new_ptr;

	ft_putstr("\nf(update_malloc)");
    if (block->size >= size)
    {
		ft_putstr("\nf(if block->size >= size), create block");
        return (block->ptr);
    }
    else // if (block->size < size)
    {
		show_alloc_mem();		
		ft_putstr("\nf(if block->size < size). free& malloc, snewize :");
		ft_putnbr_base((long)size, 10);
		ft_putstr(" oldsize :");
		ft_putnbr_base((long)block->size, 10);
		
		new_ptr = malloc(size);
		
		ft_putstr(" realloc addr new_ptr malloced "); ft_putnbr_base((long)new_ptr, 16);		
		
		new_ptr = ft_memcpy(new_ptr, block->ptr, block->size);
		free(block->ptr);
		return (new_ptr);
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
			return update_malloc(block, size);
		block = block->next;
	}
	ft_putstr("\nBM ::: END\n");
    return NULL;
}

static void		*find_map(t_map **map, void *ptr, size_t size, int type, int page)
{
	ft_putstr("\nf(find_map)");
	
  	if ((long)((void*)*map + getpagesize() * page) == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
  	{
		ft_putstr("\nMap found");
		return browse_found_map(map, ptr - BLOCK_SIZE, size);
	}
	else if (type != LARGE && (*map)->page_count > (size_t)page)
	{
		ft_putstr("\npage->count "); ft_putnbr_base((long)(*map)->page_count, 10);
		return find_map(map, ptr, size, type, page + 1);
	}
	else if ((*map)->next)
	{
		ft_putstr(" map->next");
		return find_map(&(*map)->next, ptr, size, type, 0);
	}
	return NULL;
}

void			*realloc(void *ptr, size_t size)
{
	int		type;
    void    *realloced_ptr;
	ft_putstr("\nf(realloc), ptr: ");ft_putnbr_base((long)ptr, 16);
	ft_putstr(" , size : ");ft_putnbr_base((long)size, 10);	
	show_alloc_mem();

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
			if ((realloced_ptr = find_map(&g_types_tab[type], ptr, size, type, 0)))
			{
				show_alloc_mem();
				return realloced_ptr;
			}
		}
		type++;
	}
	show_alloc_mem();

	ft_putstr("\nf(realloc) NOTHING FOUND: ");ft_putnbr_base((long)ptr, 16);	
    return ptr;
}