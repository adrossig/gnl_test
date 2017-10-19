/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:51:23 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/18 22:40:49 by sgardner         ###   ########.fr       */
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
	print_alloc_report(1);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		count;
	int		i;

	fprintf(stderr,	"\nRunning %d iterations with BUFF_SIZE %d...\n",
			ITER, BUFF_SIZE);
	fprintf(stderr, "Increase BUFF_SIZE or decrease ITER in run_test.sh if"
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
		while (get_next_line(fd, &line) > 0)
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
