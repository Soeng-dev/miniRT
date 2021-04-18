NAME = miniRT

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

EXT_STLIB = -lmlx -framework OpenGL -framework AppKit ./libft/libft.a 
EXT_DYLIB = ./libmlx.dylib
EXT_DYLIB_PATH = ./mlx_mms/
EXT_LIB = $(EXT_STLIB) $(EXT_DYLIB_PATH)$(EXT_DYLIB)

SRC = ./utils/mymlx_utils.c						\
	  ./utils/bmp_tools.c						\
	  ./utils/math/math_calc_tools.c			\
	  ./utils/math/math_oper_tools.c			\
	  ./utils/math/myvector.c					\
	  ./utils/math/vector_tools.c				\
	  ./utils/math/vector_operation.c			\
	  ./utils/math/vector_calculation.c			\
	  ./ray_tracing/camera.c					\
	  ./ray_tracing/hit_record.c				\
	  ./ray_tracing/material_reflect.c			\
	  ./ray_tracing/light.c						\
	  ./ray_tracing/ray.c						\
	  ./ray_tracing/figures/cylinder.c			\
	  ./ray_tracing/figures/plane.c				\
	  ./ray_tracing/figures/sphere.c			\
	  ./ray_tracing/figures/square.c			\
	  ./ray_tracing/figures/triangle.c			\
	  ./manage_command/exit_and_error.c			\
	  ./manage_command/read_command.c			\
	  ./manage_command/set_view.c				\
	  ./manage_command/diverge_command.c		\
	  ./manage_command/set_figures_mandatory.c	\
	  ./manage_command/string_manage.c			\
	  ./manage_command/change/change_cam_light.c\
	  ./manage_command/change/change_property.c	\
	  ./manage_command/change/change_figure.c	\
	  ./manage_command/change/select_change.c	\
	  ./manage_command/change/transformation.c	\
	  ./get_next_line/get_next_line.c			\
	  ./get_next_line/get_next_line_utils.c		\
	  ./main.c
	  
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) all_libft all_mlx_mms
		cp $(EXT_DYLIB_PATH)$(EXT_DYLIB) ./
		$(CC) $(CFLAGS) $(EXT_LIB) $(OBJ) -o $(NAME)


RM = rm -f

clean : clean_libft clean_mlx_mms
	$(RM) $(OBJ)
	
fclean : clean fclean_libft fclean_mlx_mms
	$(RM) $(NAME)
	$(RM) $(EXT_DYLIB)

re: fclean all



############### External library make command #################

# libft
all_libft :
		$(MAKE) -C ./libft all bonus

clean_libft : 
		$(MAKE) -C ./libft clean

fclean_libft : 
		$(MAKE) -C ./libft fclean


# minilibx_mms compile
all_mlx_mms :
		$(MAKE) -C ./mlx_mms all

clean_mlx_mms : 
		$(MAKE) -C ./mlx_mms clean

fclean_mlx_mms :
		$(MAKE) -C ./mlx_mms fclean


.PHONY: all clean fclean re libft mlx_mms 
