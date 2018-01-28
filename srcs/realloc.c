#include "../includes/malloc.h"

static t_block		*update_malloc(t_map **map, t_block *block, size_t size)
{
    size_t  oldsize;

    if (block->size >= size)
    {
        oldsize = block->size;
        block->size = size;
        if (!block->next || block->next->free == FALSE)
            block->next = create_block(*map, BLOCK_SIZE + size, block, block->next);
        else if (block->next->free == TRUE)
        {
            block->next = create_block(*map, oldsize - size + block->next->size,
                block, (void*)block + BLOCK_SIZE + size);
        }  
        return (block->ptr);
    }
    else if (block->size < size)
    {
        free(block->ptr);
        return (malloc(size));
    }
}

static t_block		*browse_found_map(t_map **map, t_block *to_realloc, size_t size)
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

static t_block	*find_map(void *ptr, int type, size_t size, size_t page)
{
	void	*page_addr;
    t_map   **map;
    t_block *block;

    map = &g_types_tab[type];
  	if ((long)((void*)*map + getpagesize() * page) == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
  	{
		ft_putstr("\nMap found");
	 	return browse_found_map(map, ptr - BLOCK_SIZE, size);
	}
	else if (type != LARGE && (*map)->page_count > page)
		find_map(map, ptr, type, page + 1);
	else if ((*map)->next)
		find_map(&(*map)->next, ptr, type, 0);
	return NULL;
}

void			*realloc(void *ptr, size_t size)
{
	int		type;
    void    *realloced_ptr;
	ft_putstr("\nf(realloc)");

	type = 0;
	while (type < MAX_TYPE)
	{
		if (g_types_tab[type]) {
			if ((realloced_ptr = find_map(ptr, type, size, 0)))
				return realloced_ptr;
		}
		type++;
	}
    return NULL;
}