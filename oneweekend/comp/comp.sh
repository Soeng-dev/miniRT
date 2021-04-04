#!/bin/bash
./rmgch.sh
gcc -lmlx -framework OpenGL -framework AppKit $1 miniRT.h main.c libft/*.? utils/*.? ray_tracing/*.? manage_command/*.? get_next_line/*.?
