static void		*update_malloc(t_map **map, t_block *block, size_t size, int type)
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
		// show_alloc_mem();		
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