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

# define TRUE 1
# define FALSE 0

# define TINY_SIZE 16
# define SMALL_SIZE 512

enum						e_type
{
	TINY,
	SMALL,
	LARGE,
	MAX_TYPE
};

enum						e_state
{
	FULL,
	MAX_TYPE
};

typedef struct				s_map_data
{
		int					map_type;
		size_t				map_size;

}							t_map_data;

typedef struct				s_block
{
		size_t				size;
		struct s_block		*next;
		struct s_block		*prev;
		int					free;
		void				*ptr;

}							t_block;

typedef struct				s_map
{
		struct s_map		*next;
		struct s_block		*block;
		int					state;

}							t_map;

typedef struct				s_maps
{
		struct s_map		*tiny;
		struct s_map		*small;
		struct s_map		*large;

}							t_maps;


# define BLOCK_SIZE (sizeof(struct s_block))

extern t_maps				maps;

void						*malloc(size_t size);
int							get_type(size_t size);

#endif
