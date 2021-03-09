#!/bin/bash
gcc -lmlx -framework OpenGL -framework AppKit miniRT.h main.c $1
