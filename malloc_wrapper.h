/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrapper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 01:56:12 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/18 22:40:24 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_WRAPPER_H
# define MALLOC_WRAPPER_H

extern size_t	g_bytes_allocated;
extern size_t	g_bytes_freed;
extern int		g_num_frees;
extern int		g_num_mallocs;

typedef struct	s_alloc
{
	void			*ptr;
	size_t			size;
	struct s_alloc	*next;
}				t_alloc;

void			print_alloc_report(int print_address);
#endif
