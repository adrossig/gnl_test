/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 01:56:25 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/18 22:55:35 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "malloc_wrapper.h"

static	t_alloc	*g_head;
size_t	g_bytes_allocated;
size_t	g_bytes_freed;
int		g_num_frees;
int		g_num_mallocs;

static void	add_ptr(void *ptr, size_t size)
{
	void *(*libc_malloc)(size_t) =
		(void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
	t_alloc	*alloc;

	if (!(alloc = libc_malloc(sizeof(t_alloc))))
	{
		printf("Not enough memory for malloc wrapper.\nExiting...\n");
		exit(1);
	}
	g_bytes_allocated += size;
	g_num_mallocs++;
	alloc->ptr = ptr;
	alloc->size = size;
	alloc->next = g_head;
	g_head = alloc;
}

static void	remove_ptr(void *ptr)
{
	void (*libc_free)(void *) = (void (*)(void *))dlsym(RTLD_NEXT, "free");
	t_alloc	**head;
	t_alloc	*next;

	head = &g_head;
	while (*head && (*head)->ptr != ptr)
		head = &(*head)->next;
	if (*head && (*head)->ptr == ptr)
	{
		g_num_frees++;
		g_bytes_freed += (*head)->size;
		next = (*head)->next;
		libc_free(*head);
		*head = next;
	}
}

void		print_alloc_report(int print_address)
{
	void (*libc_free)(void *) = (void (*)(void *))dlsym(RTLD_NEXT, "free");
	t_alloc	*next;
	size_t	leaked_bytes;

	fprintf(stderr, "%-26s %d (%lu bytes)\n", "Total allocations:",
			g_num_mallocs, g_bytes_allocated);
	fprintf(stderr, "%-26s %d (%lu bytes)\n", "Total freed allocations:",
			g_num_frees, g_bytes_freed);
	fprintf(stderr, "%-26s %d\n\n", "Memory leaks:",
			g_num_mallocs - g_num_frees);
	if (!print_address)
		return ;
	leaked_bytes = 0;
	while (g_head)
	{
		leaked_bytes += g_head->size;
		fprintf(stderr, "%p (%lu bytes)\n", g_head->ptr, g_head->size);
		next = g_head->next;
		libc_free(g_head->ptr);
		libc_free(g_head);
		g_head = next;
	}
	fprintf(stderr, "\nTotal bytes leaked: %lu\n\n", leaked_bytes);
}

void 		*malloc(size_t size)
{
	void	*ptr;
	void *(*libc_malloc)(size_t) =
		(void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");

	if ((ptr = libc_malloc(size)))
		add_ptr(ptr, size);
	return (ptr);
}

void 		free(void *ptr)
{
	void (*libc_free)(void *) = (void (*)(void *))dlsym(RTLD_NEXT, "free");
	
	remove_ptr(ptr);
	return (libc_free(ptr));
}
