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

enum	e_type
{
	TINY,
	SMALL,
	LARGE,
	MAX_TYPE
};

typedef char				t_bool;

// mmap result -> mapping

typedef struct				s_block
{
		t_bool				free;
		size_t				size;
		void				*ptr;
		struct s_block		*prev;
		struct s_block		*next;
}							t_block;

// list of mapping for a given type
typedef struct				s_map
{
	size_t					free_space;
	size_t					page_count;	
	struct s_block			*block;
	struct s_map			*prev;
	struct s_map			*next;
	struct s_map			*last;
}							t_map;

# define TINY_SIZE 16
# define SMALL_SIZE 512

# define TRUE 1
# define FALSE 0

# define EMPTY 0
# define FULL 1


# define BLOCK_SIZE (sizeof(t_block))
# define MAP_SIZE (sizeof(t_map))

// global types tab
extern t_map				*g_types_tab[MAX_TYPE];


void						*malloc(size_t size);
void						*realloc(void *ptr, size_t size);
void						free(void *ptr);

t_map		 				*get_map_lst(int type, size_t size);

t_map						*create_map(int type, size_t size, t_map *prevmap);

t_block						*create_block(t_map *map, size_t size,
							t_block *prev_block, t_block *next_block);
t_block						*get_block(t_map *map, int type, size_t size);



int							get_type(size_t size);
size_t						get_size(size_t size);

void						ft_putstr(char *str);
void						ft_putnbr_base(long n, int base);

void						wander_types(void *ptr);

void						show_alloc_mem(void);

#endif
