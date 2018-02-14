# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpoblon <gpoblon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/02 15:03:29 by aditsch           #+#    #+#              #
#    Updated: 2018/02/08 22:02:18 by gpoblon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so

NAME_LINK = libft_malloc_$(HOSTTYPE).so

SRCS =	srcs/thread_safe.c \
		srcs/malloc.c \
		srcs/free.c \
		srcs/realloc.c \
		srcs/reallocf.c \
		srcs/maps.c \
		srcs/blocks.c \
		srcs/utils.c \
		srcs/show_alloc_mem.c \
		srcs/calloc.c \
		srcs/show_alloc_mem_full.c \
		srcs/show_alloc_mem_hex.c \

INC_PATH = includes/

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wextra -Wall -fpic -I$(INC_PATH)

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