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

typedef struct				s_block
{
		size_t				size;
		struct s_block		*next;
		struct s_block		*prev;
		int					free;
		void				*ptr;
}							t_block;

typedef struct				s_maps_list
{
	struct s_maplist		*next;
	int						state;
	struct t_block			*block;
}							t_mlist;

# define TINY_SIZE 16
# define SMALL_SIZE 512

# define TRUE 1
# define FALSE 0

# define META_BLOCK_SIZE (sizeof(struct s_block))
# define META_MLIST_SIZE (sizeof(struct s_mlist))

# define ALIGN_4(x) (((((x) - 1) >> 2) << 2) + 4)

extern t_mlist 				g_tab_maps[MAX_TYPE];

void						*malloc(size_t size);
int							get_type(size_t size);

#endif
