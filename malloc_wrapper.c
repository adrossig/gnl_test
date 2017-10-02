/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 01:56:25 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/01 03:30:50 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "malloc_wrapper.h"

size_t	g_bytes_allocated;
int		g_num_frees;
int		g_num_mallocs;

void *malloc(size_t size)
{
	void *(*libc_malloc)(size_t) =
		(void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");

	g_bytes_allocated += size;
	g_num_mallocs++;
	return (libc_malloc(size));
}

void free(void *ptr)
{
	void (*libc_free)(void *) = (void (*)(void *))dlsym(RTLD_NEXT, "free");

	g_num_frees++;
	return (libc_free(ptr));
}
