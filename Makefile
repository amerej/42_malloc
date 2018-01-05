# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aditsch <aditsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/02 15:03:29 by aditsch           #+#    #+#              #
#    Updated: 2017/12/04 10:45:46 by aditsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so

NAME_LINK = libft_malloc_$(HOSTTYPE).so

SRCS =	srcs/malloc.c \
		srcs/maps.c \
		srcs/utils.c

INC_PATH = includes/

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Werror -Wextra -Wall -I$(INC_PATH)

#LDLIBS = -lft -lpthread

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(NAME_LINK)
	rm $(NAME) 2> /dev/null || true
	ln -s $(NAME_LINK) $(NAME)

$(NAME_LINK): $(OBJS)
	$(CC) -shared $(CFLAGS) -o $(NAME_LINK) $(OBJS)

clean:
	rm -fv $(OBJS)

fclean: clean
	rm -fv $(NAME) $(NAME_LINK)

re: fclean all