# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 15:17:00 by jcourtoi          #+#    #+#              #
#    Updated: 2021/12/06 17:18:45 by jcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
       ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c  ft_striteri.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

SRCSBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	    ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	    ft_lstmap.c

OBJ = $(SRCS:.c=.o)
OBJBONUS = $(SRCSBONUS:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra

AR = ar rcs

all: $(NAME)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(SRCSBONUS)
	gcc -nostartfiles -shared -o libft.so $(OBJ) $(OBJBONUS)

compile: 
	$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	 $(AR) $(NAME) $(OBJ)

bonus:  $(OBJBONUS)
	$(AR) $(NAME) $(OBJBONUS)
clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
