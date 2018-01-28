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
		ft_putstr("\nf(if block->size < size). free& malloc");
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

static t_block	*find_map(t_map **map, void *ptr, size_t size, int type)
{
	ft_putstr("\nf(find_map)");
	void	*lastpage;
	
	lastpage = *map + (getpagesize() * (*map)->page_count);
  	if ((long)*map == ((long)ptr & 0xFFFFFFFFF000)) // remove FFF on macOS
  	{
		ft_putstr("\nMap found");
	 	return browse_found_map(map, ptr - BLOCK_SIZE, size, type);
	}
	else if (type != LARGE && (void*)*map < lastpage)
	{
		ft_putstr("page->count");
		find_map(map + getpagesize(), ptr, size, type);
	}
	else if ((*map)->next)
	{
		ft_putstr("map->next");
		find_map(&(*map)->next, ptr, size, type);
	}
	return NULL;
}

void			*realloc(void *ptr, size_t size)
{
	int		type;
    void    *realloced_ptr;
	ft_putstr("\nf(realloc)");

	type = 0;
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	while (type < MAX_TYPE)
	{
		if (g_types_tab[type]) {
			if ((realloced_ptr = find_map(&g_types_tab[type], ptr, size, type)))
				return realloced_ptr;
		}
		type++;
	}
    return NULL;
}