static void		*update_malloc(t_map **map, t_block *block, size_t size, int type)
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
		ft_putstr(" addr malloc "); ft_putnbr_base((long)malloc(size), 16);		
		show_alloc_mem();
		// new_ptr = ft_memcpy(new_ptr, block->ptr, block->size);
		malloc(size);
		return NULL;
    }
}