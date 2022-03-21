# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sclam <sclam@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 22:03:23 by sclam             #+#    #+#              #
#    Updated: 2022/03/20 15:56:34 by sclam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	srcs/list_manipulation.c \
			srcs/list_manipulation2.c \
			srcs/list_manipulation3.c \
			srcs/parser.c \
			srcs/parser_utils.c \
			srcs/parser_utils2.c \
			srcs/ft_charjoin.c \
			srcs/cmd_lists.c \
			srcs/split_with_quotes.c \
			srcs/minishell.c \
			srcs/sort_list.c \
			srcs/free_functions.c \
			srcs/dollar.c \
			srcs/check_redirect.c \
			srcs/redirect.c \
			srcs/redirect_str.c \
			srcs/redirect_lists.c \
			srcs/env_arr.c \
			srcs/builtins.c \
			srcs/builtins2.c \
            srcs/child.c \
            srcs/export_utils.c \
            srcs/builtins_utils.c \
			srcs/builtins_exec.c \
			srcs/fd_handling.c \
			srcs/open_redirects.c \
            srcs/exit.c \
			srcs/heredoc.c \
			srcs/signals.c

CC		=	gcc

FLAGS	=	-lreadline

WWW		=	-Wall -Wextra -Werror

LIBFT	=	/libft/libft.a

HEAD	= 	includes/minishell.h

OBJS	=	${SRCS:.c=.o}

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	UNAME_M := $(shell uname -m)
	ifeq ($(UNAME_M),x86_64)
		FLAGS   += -I${HOME}/.brew/opt/readline/include
		LDLIBS  += -L${HOME}/.brew/opt/readline/lib
	endif
	ifeq ($(UNAME_M),arm64)
		FLAGS   += -I/opt/homebrew/opt/readline/include
		LDLIBS  += -L/opt/homebrew/opt/readline/lib
	endif
endif

.PHONY: all clean fclean re

.c.o:
	$(CC) $(WWW) -c $< -o $@

$(NAME): $(SRCS) $(OBJS) $(HEAD)
	@make -C ./libft
	$(CC) $(FLAGS) $(WWW) $(OBJS) $(LDLIBS) -I $(HEAD) -o $(NAME) -L./libft -lft

all : $(NAME)

clean :
	rm -rf $(OBJS)
	@make clean -C ./libft

fclean : clean
	rm -rf $(NAME)
	@make fclean -C ./libft

re : fclean all