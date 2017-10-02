#!/bin/sh
gcc -fno-common -c malloc_wrapper.c
gcc -dynamiclib -o libmwrapper.dylib malloc_wrapper.o
make -C ../libft fclean
make -C ../libft
gcc -Wall -Werror -Wextra -I . -I ../libft/includes -L ../libft -l ft -L . -l mwrapper test.c ../get_next_line.c -o gnl_test
/usr/bin/time -lp ./gnl_test big.txt 1>/dev/null
echo "\nTest complete."
rm malloc_wrapper.o libmwrapper.dylib gnl_test
