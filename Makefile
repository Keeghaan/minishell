# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboratko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 15:13:15 by nboratko          #+#    #+#              #
#    Updated: 2022/09/19 15:14:12 by nboratko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/main.c srcs/envp_utils.c srcs/mini_utils.c srcs/tokens/tokens.c\
	srcs/tokens/advanced_tokens.c srcs/tokens/expander.c\
	srcs/signals.c srcs/tokens/tokens_utils.c srcs/tokens/expander_utils.c\
	srcs/parsing/parse.c srcs/parsing/cmds.c srcs/parsing/path_utils.c\
	srcs/exec/pipex.c srcs/exec/pipex_utils.c srcs/check_args.c \
	srcs/exec/run_cmd.c srcs/exec/exec_utils.c srcs/mini_utils2.c\
	builtins/exit.c builtins/export.c builtins/cd.c builtins/get_cwd.c \
	srcs/exec/error_msg.c srcs/exec/here_doc.c srcs/init.c builtins/env.c\
	srcs/parsing/other_cases.c builtins/unset.c srcs/free.c\
	builtins/fake_export.c srcs/exec/pipex_loop.c srcs/tokens/tokens_utils2.c

_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m
_END=	$'\033[0m

OBJS = ${SRCS:.c=.o}

INCLUDE =	-I inc\
		-I libft

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

HEADER = inc/minishell.h

all: ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

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

re: fclean
	@make all

test:	$(NAME)
	./$(NAME)

fdtest:	$(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup_rl_error --track-fds=yes ./$(NAME)

vtest:	$(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup_rl_error ./$(NAME)

.PHONY: all clean fclean re bonus test vtest
