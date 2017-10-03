#!/bin/sh
ITER="50"
BUFF_SIZE="32"
gcc -fno-common -c malloc_wrapper.c
gcc -dynamiclib -o libmwrapper.dylib malloc_wrapper.o
make -C ../libft fclean
make -C ../libft
sed -i '' -e "s/.*define.*ITER.*/# define ITER $ITER/" test.c
sed -i '' -e "s/.*define.*BUFF_SIZE.*/# define BUFF_SIZE $BUFF_SIZE/" ../get_next_line.h
gcc -Wall -Werror -Wextra -I . -I ../libft/includes -L ../libft -l ft -L . -l mwrapper test.c ../get_next_line.c -o gnl_test
/usr/bin/time -lp ./gnl_test big.txt 1>/dev/null
echo "\nTest complete."
rm malloc_wrapper.o libmwrapper.dylib gnl_test
