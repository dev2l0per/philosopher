# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juyang <juyang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/28 16:26:26 by juyang            #+#    #+#              #
#    Updated: 2021/03/28 16:26:28 by juyang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = monitoring.c \
       solve.c \
       utils.c \
       init.c \
       main.c \
	   utils2.c

OBJS = $(SRCS:%.c=%.o)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS)

%.o : %.c
			$(CC) $(CFLAGS) -pthread -o $@ -c $<

all:		$(NAME)

clean:
			rm -rf $(OBJS)

fclean:
			rm -rf $(OBJS)
			rm -rf $(NAME)

re: fclean all
