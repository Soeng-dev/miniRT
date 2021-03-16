#!/bin/bash

gcc diffused_main.c miniRT.h libft/*.? utils/*.? ray_tracing/*.? $1 -lbsd -lmlx -lXext -lX11 -lm
