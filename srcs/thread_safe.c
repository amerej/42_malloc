/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:33:53 by gpoblon           #+#    #+#             */
/*   Updated: 2018/02/04 16:39:58 by gpoblon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void			*malloc(size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	new_ptr = ts_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ts_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void			*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	new_ptr = ts_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}

void			*reallocf(void *ptr, size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	new_ptr = ts_reallocf(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}

void			*calloc(size_t count, size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	new_ptr = ts_calloc(count, size);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}
