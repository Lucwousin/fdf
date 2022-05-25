# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsinke <lsinke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/20 14:57:29 by lsinke        #+#    #+#                  #
#    Updated: 2022/04/20 14:57:29 by lsinke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fdf

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/

SRCS = cam.c\
	   colour.c\
	   draw_line.c\
	   fdf.c\
	   hooks.c\
	   init.c\
	   line_colour.c\
	   matrix.c\
	   parser.c\
	   render.c\
	   rotate.c

OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJS))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/
LIBFT_LIB = $(addprefix $(LIBFT), libft.a)
LIBFT_INC = -I ./libft/include

MLX = ./MLX42/
MLX_LIB = $(addprefix $(MLX), libmlx42.a)
MLX_INC = -I ./MLX42/include

ifeq ($(shell uname -s), Darwin)
	MLX_ARG = -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/
else
	MLX_ARG = -ldl -lglfw
	CFLAGS += -mavx
endif

all: libft libmlx $(NAME)

libft:
	@make -C $(LIBFT)

libmlx:
	@make -C $(MLX)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)fdf.h
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(LIBFT_INC) $(MLX_INC) -c -o $@ $<

$(NAME): $(OBJS_PREFIXED)
	@echo "Compiling main executable"
	@$(CC) $(CFLAGS) $(OBJS_PREFIXED) $(LIBFT_LIB) $(MLX_LIB) $(MLX_ARG) -lm -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Done cleaning $(CURDIR)/$(OBJ_DIR)"
	@make -C $(LIBFT) clean
	@make -C $(MLX) clean

fclean: clean
	@rm -f $(NAME)
	@echo "Done cleaning archive $(CURDIR)/$(NAME)"
	@make -C $(LIBFT) fclean
	@make -C $(MLX) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
