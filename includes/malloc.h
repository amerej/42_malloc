/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:39:37 by aditsch           #+#    #+#             */
/*   Updated: 2018/01/07 01:22:46 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>

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
	struct s_block			*block;
	struct s_map			*next;
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

t_map		 				*get_map_lst(int type, size_t size);

t_map						*create_map(int type, size_t size);

t_block						*create_block(t_map *map, size_t size,
							t_block *prev_block, t_block *next_block);
t_block						*get_block(t_map *map, int type, size_t size);



int							get_type(size_t size);
int							get_size(size_t size);

void						ft_putstr(char *str);
void						ft_putnbr_hex(long n);
void						ft_putnbr(long n);

#endif
