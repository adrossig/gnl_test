/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrossig <adrossig@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:51:23 by sgardner          #+#    #+#             */
/*   Updated: 2020/09/12 20:54:13 by adrossig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define ITER 50
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../get_next_line.h"
#include "malloc_wrapper.h"

static void	print_report(int count)
{
	fprintf(stderr, "%-26s %d\n", "Lines allocated and freed:", count);
	fprintf(stderr, "%-26s %d\n", "Data structures allocated:",
			g_num_mallocs - count);
	fprintf(stderr, "%-26s %d\n", "Data structures freed:",
			g_num_frees - count);
	print_alloc_report(0);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		count;
	int		i;

	fprintf(stderr,	"\nRunning %d iterations with BUFFER_SIZE %d...\n",
			ITER, BUFFER_SIZE);
	fprintf(stderr, "Increase BUFFER_SIZE or decrease ITER in run_test.sh if"
			" test takes too long.\n");
	i = 0;
	while (i++ < ITER)
	{
		if (argc == 2)
		{
			if ((fd = open(argv[1], O_RDONLY)) == -1)
				return (1);
		}
		else
			fd = 0;
		line = NULL;
		count = 0;
		while ((get_next_line(fd, &line)) == 1)
		{
			printf("%s\n", line);
			free(line);
			count++;
		}
		if (close(fd) == -1)
			return (1);
	}
	fprintf(stderr, "\n%-26s %p\n", "EOF. *line points to:", (void *)line);
	print_report(count);
	return (0);
}
