#!/bin/sh
FILE="big.txt"
ITER="50"
BUFFER_SIZE="32"
PRINT_ADDRESS="0"
gcc -fno-common -c malloc_wrapper.c
gcc -dynamiclib -o libmwrapper.dylib malloc_wrapper.o
sed -i '' -e "s/.*define.*ITER.*/# define ITER $ITER/" test.c
sed -i '' -e "s/.*print_alloc_report.*/	print_alloc_report($PRINT_ADDRESS);/" test.c
sed -i '' -e "s/.*define.*BUFF_SIZE.*/# define BUFF_SIZE $BUFF_SIZE/" ../get_next_line.h
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=$BUFFER_SIZE malloc_wrapper.c test.c ../get_next_line.c ../get_next_line_utils.c -o gnl_test
/usr/bin/time -lp ./gnl_test $FILE 1>/dev/null
echo "\nTest complete."
rm malloc_wrapper.o libmwrapper.dylib gnl_test
