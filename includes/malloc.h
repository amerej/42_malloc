/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:39:37 by aditsch           #+#    #+#             */
/*   Updated: 2017/12/17 20:25:31 by aditsch          ###   ########.fr       */
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

typedef t_bool				char;

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
	struct t_block			*block;
	struct s_maplist		*next;
}							t_map;

# define TINY_SIZE 16
# define SMALL_SIZE 512

# define TRUE 1
# define FALSE 0

# define EMPTY 0
# define FULL 1


# define META_BLOCK_SIZE (sizeof(struct s_block))
# define META_MAP_SIZE (sizeof(struct s_mlist))

# define ALIGN_4(x) (((((x) - 1) >> 2) << 2) + 4)

// global types tab
extern t_map				*g_types_tab[MAX_TYPE];


void						*malloc(size_t size);

t_map		 				*get_map_lst(int type, size_t size);

t_block						*create_block(t_map **map_list, size_t size);
t_block						*get_block(t_map *map_list, int type, size_t size);



int							get_type(size_t size);
int							get_size(size_t size);

#endif
