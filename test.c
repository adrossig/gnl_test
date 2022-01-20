/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arossign <arossign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:51:23 by sgardner          #+#    #+#             */
/*   Updated: 2022/01/20 12:52:37 by arossign         ###   ########.fr       */
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

int			main()
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
		line = NULL;
		count = 0;
		if ((fd = open("big.txt", O_RDONLY)) == -1)
			return (1);
		line = get_next_line(fd);
		while (line != NULL)
		{
			printf("%s\n", line);
			free(line);
			count++;
			line = get_next_line(fd);
		}
		if (close(fd) == -1)
			return (1);
	}
	fprintf(stderr, "\n%-26s %p\n", "EOF. *line points to:", (void *)line);
	print_report(count);
	return (0);
}
