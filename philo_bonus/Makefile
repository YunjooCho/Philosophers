# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 19:16:02 by yunjcho           #+#    #+#              #
#    Updated: 2023/04/03 17:52:06 by yunjcho          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
SRCS = main.c init.c parsing.c print.c task1.c task2.c thread.c timer.c
OBJS = $(SRCS:.c=.o)
DBJS = $(SRCS:.c=.d)

ifdef SANITIZE
	CFLAGS += -fsanitize=address
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

clean :
	rm -rf $(OBJS)
	rm -rf $(DBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

bonus :
	make BONUS=1 all

sanitize :
	make SANITIZE=1 re

.PHONY: all clean fclean re bonus sanitize
