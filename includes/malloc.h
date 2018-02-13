/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:39:37 by aditsch           #+#    #+#             */
/*   Updated: 2018/02/06 11:57:23 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <sys/resource.h>
# include <pthread.h>

enum	e_type
{
	TINY,
	SMALL,
	LARGE,
	MAX_TYPE
};

typedef char			t_bool;

typedef struct			s_block
{
	t_bool				free;
	size_t				size;
	void				*ptr;
	struct s_block		*next;
}						t_block;

typedef struct			s_map
{
	size_t				free_space;
	size_t				page_count;
	int					type;
	struct s_block		*block;
	struct s_map		*prev;
	struct s_map		*next;
	struct s_map		*last;
}						t_map;

# define TINY_SIZE 16
# define SMALL_SIZE 512

# define TRUE 1
# define FALSE 0

# define EMPTY 0
# define FULL 1

# define BLOCK_SIZE (sizeof(t_block))
# define MAP_SIZE (sizeof(t_map))

# define PTHREAD_MUTEX_INIT 0

extern t_map			*g_types_tab[MAX_TYPE];
extern pthread_mutex_t	g_mutex;

void					*malloc(size_t size);
void					*ts_malloc(size_t size);
void					free(void *ptr);
void					ts_free(void *ptr);
void					*realloc(void *ptr, size_t size);
void					*ts_realloc(void *ptr, size_t size);
void					*calloc(size_t count, size_t size);
void					*ts_calloc(size_t count, size_t size);
void					*reallocf(void *ptr, size_t size);
void					*ts_reallocf(void *ptr, size_t size);

t_map					*get_map_lst(int type, size_t size);
t_map					*create_map(int type, size_t size, t_map *prevmap);

t_block					*get_block(t_map *map, int type, size_t size);
t_block					*create_block(t_map *map, size_t size,
							t_block *prev_block, t_block *next_block);

int						get_type(size_t size);
size_t					get_size(size_t size);

void					ft_putstr(char *str);
void					ft_putnbr_base(long n, int base);

void					show_alloc_mem(void);
void					show_alloc_mem_full(void);
void					show_alloc_mem_hex(void);

#endif
