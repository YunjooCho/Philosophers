# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 19:16:02 by yunjcho           #+#    #+#              #
#    Updated: 2023/03/29 15:59:10 by yunjcho          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_backup
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
SRCS = main.c parsing.c init.c array.c thread.c mutex.c timer.c print.c
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

# -include $(addprefix philo/, $(DBJS)) #header 파일 수정 시 make re / 기능 별도 확인