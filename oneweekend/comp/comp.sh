#!/bin/bash
./rmgch.sh
gcc -lmlx -framework OpenGL -framework AppKit $1 miniRT.h main.c libft/*.? utils/*.? get_next_line/* ray_tracing/*.? 
