#include "../includes/malloc.h"

static t_block		*update_malloc(t_map **map, t_block *block, size_t size, int type)
{
	int		newsize;

	ft_putstr("\nf(update_malloc)");
	newsize = 0;
    if (block->size >= size)
    {
		ft_putstr("\nf(if block->size >= size), create block");
		if (type != LARGE)
			return (block->ptr); // possible but trash 
        else if (block->next->free == FALSE || !block->next) // the latter shouldnt happen
		{
			ft_putstr("\n!block->next->free == FALSE");			
			newsize = block->size - (size + BLOCK_SIZE);
			if (newsize > 0)
			{
				ft_putstr("\nnewsize > 0");				
				block->size = size;
				block->next = create_block(*map, newsize, block, block->next);
				(*map)->free_space += newsize;
			}
		}
        else // if (block->next->free == TRUE)
        {
			ft_putstr("\nblock->next->free == TRUE");
			newsize = block->size - size + block->next->size;
			block->size = size;
           	block->next = create_block(*map, newsize, block, block->next->next);
			(*map)->free_space += block->size - size;
        }
		if (block->next && block->next->next)
			block->next->next->prev = block->next;
        return (block->ptr);
    }
    else // if (block->size < size)
    {
		ft_putstr("\nf(if block->size < size). free& malloc, size");
		ft_putstr(" type "); ft_putnbr_base((long)type, 10);
        free(block->ptr);
		return (malloc(size));
    }
}

static t_block		*browse_found_map(t_map **map, t_block *to_realloc, size_t size, int type)
{
	t_block		*block;

	ft_putstr("\nf(browse_map)");

	block = (*map)->block; // NO MAPS BLOCK
	while (block)
	{
		if (block == to_realloc) // NE RENTRE PAS DANS LA CDT
			return update_malloc(map, block, size, type);
		block = block->next;
	}
	ft_putstr("\nBM ::: END\n");
    return NULL;
}

static t_block	*find_map(t_map **map, void *ptr, size_t size, int type, int page)
{
	ft_putstr("\nf(find_map)");
	
  	if ((long)((void*)*map + getpagesize() * page) == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
  	{
		ft_putstr("\nMap found");
	 	return browse_found_map(map, ptr - BLOCK_SIZE, size, type);
	}
	else if (type != LARGE && (*map)->page_count > (size_t)page)
	{
		ft_putstr("\npage->count "); ft_putnbr_base((long)(*map)->page_count, 10);
		find_map(map, ptr, size, type, page + 1);
	}
	else if ((*map)->next)
	{
		ft_putstr("map->next");
		find_map(&(*map)->next, ptr, size, type, 0);
	}
	return NULL;
}

void			*realloc(void *ptr, size_t size)
{
	int		type;
    void    *realloced_ptr;
	ft_putstr("\nf(realloc), ptr:");ft_putnbr_base((long)ptr, 16);

	show_alloc_mem();

	type = 0;
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	while (type < MAX_TYPE)
	{
		if (g_types_tab[type]) {
			ft_putstr("\nglobal "); ft_putnbr_base((long)&g_types_tab[type], 16);
			ft_putstr(" type "); ft_putnbr_base((long)type, 10);			
			if ((realloced_ptr = find_map(&g_types_tab[type], ptr, size, type, 0)))
				return realloced_ptr;
		}
		type++;
	}
    return ptr;
}