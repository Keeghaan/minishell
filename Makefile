# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboratko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 15:13:15 by nboratko          #+#    #+#              #
#    Updated: 2022/09/06 14:12:05 by jcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/main.c srcs/envp_utils.c srcs/mini_utils.c srcs/tokens/tokens.c\
	srcs/tokens/advanced_tokens.c srcs/tokens/expander.c\
	srcs/signals.c srcs/tokens/tokens_utils.c\
	srcs/parsing/parse.c srcs/parsing/cmds.c srcs/parsing/path_utils.c\
	srcs/exec/pipex.c srcs/exec/pipex_utils.c srcs/check_args.c \
	srcs/exec/execve.c srcs/exec/run_cmd.c srcs/exec/exec_utils.c\
	builtins/exit.c builtins/export.c builtins/cd.c builtins/get_cwd.c \

_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m
_END=	$'\033[0m

OBJS = ${SRCS:.c=.o}

INCLUDE = inc

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

HEADER = inc/minishell.h

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	@make -C ./libft
	@echo "$(_GREEN)Libft compiled$(_END)"
	@make -C ./ft_printf
	@echo "$(_GREEN)Ft_printf compiled$(_END)"
	${CC} ${CFLAGS} ${OBJS} ./libft/libft.a ./ft_printf/libftprintf.a -lreadline -o ${NAME}
	@echo "$(_GREEN)Executable created : minishell$(_END)"

clean: 
	${RM} ${OBJS}
	#@make -C ./ft_printf fclean
	@make -C ./libft fclean
	@echo "$(_RED).o files removed$'\033[0m"

fclean: clean
	${RM} ${NAME}
	@echo "$(_RED)Executable removed$'\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus
