/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/07 15:01:01 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ts_reallocf(void *ptr, size_t size)
{
	void	*reallocated_ptr;

	if (size == 0)
	{
		ts_free(ptr);
		return (NULL);
	}
	else if (!(reallocated_ptr = ts_realloc(ptr, size)))
		ts_free(ptr);
	return (reallocated_ptr);
}
