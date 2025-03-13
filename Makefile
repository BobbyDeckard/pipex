# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imeulema <imeulema@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 09:02:31 by imeulema          #+#    #+#              #
#    Updated: 2025/03/05 09:02:33 by imeulema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wextra -Wall -Werror -g
RM = rm
RMFLAGS = -f
MAKE = make

# SOURCES
SRCS = $(addprefix srcs/, $(SRCS_FILES))
SRCS_FILES = main.c \
			 clean.c \
			 exec.c \
			 parse_args.c \
			 parse_path.c \
			 ft_split_path.c
PATH_SRCS = srcs/
PATH_OBJS = objs/
OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

# INCLUDES
HEADERS = incl/pipex.h
LIBFT = libft/libft.a

# TERMINAL COLORS
RED = \033[0;31m
YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0m

# RULES
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	echo "$(GREEN)$(NAME) compiled!$(RESET)"

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c $(HEADERS) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft --no-print-directory

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(MAKE) clean -C libft --no-print-directory

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	$(MAKE) fclean -C libft --no-print-directory
	echo "$(GREEN)Full clean done.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

.SILENT:
