# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsinke <lsinke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/20 12:19:17 by lsinke        #+#    #+#                  #
#    Updated: 2022/04/20 12:19:17 by lsinke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/

SRCS = ft_atoi.c\
	   ft_bzero.c\
	   ft_calloc.c\
	   ft_free_mult.c\
	   ft_hextoui.c\
	   ft_isalnum.c\
	   ft_isalpha.c\
	   ft_isascii.c\
	   ft_isdigit.c\
	   ft_isprint.c\
	   ft_itoa.c\
	   ft_lstadd_back.c\
	   ft_lstadd_front.c\
	   ft_lstclear.c\
	   ft_lstdelone.c\
	   ft_lstdelelem.c\
	   ft_lstiter.c\
	   ft_lstlast.c\
	   ft_lstmap.c\
	   ft_lstnew.c\
	   ft_lstsize.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_memcpy.c\
	   ft_memmove.c\
	   ft_memset.c\
	   ft_putchar_fd.c\
	   ft_putendl_fd.c\
	   ft_putnbr_fd.c\
	   ft_putstr_fd.c\
	   ft_simple_math.c\
	   ft_split.c\
	   ft_split_map.c\
	   ft_strchr.c\
	   ft_strdup.c\
	   ft_striteri.c\
	   ft_strjoin.c\
	   ft_strlcat.c\
	   ft_strlcpy.c\
	   ft_strlen.c\
	   ft_strmapi.c\
	   ft_strmod.c\
	   ft_strncmp.c\
	   ft_strnstr.c\
	   ft_strrchr.c\
	   ft_strtrim.c\
	   ft_substr.c\
	   ft_tolower.c\
	   ft_toupper.c\
	   get_next_line.c

OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJS))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC_DIR)libft.h $(INC_DIR)get_next_line.h
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c -o $@ $<

$(NAME): $(OBJS_PREFIXED)
	@ar -cr $(NAME) $(OBJS_PREFIXED)
	@echo "Done creating archive $(CURDIR)/$(NAME)"

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Done cleaning $(CURDIR)/$(OBJ_DIR)"

fclean: clean
	@rm -f $(NAME)
	@echo "Done cleaning archive $(CURDIR)/$(NAME)"

re: fclean all

.PHONY: all clean fclean re