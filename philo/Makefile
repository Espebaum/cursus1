# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 12:37:06 by gyopark           #+#    #+#              #
#    Updated: 2023/02/26 18:30:36 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -fsanitize=thread

SRCS			=	philo.c			\
					philo_starts.c	\
					philo_moves.c	\
					utils1.c		\
					utils2.c

OBJS			= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

all : $(NAME)

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJS)

re :
	make fclean
	make all

.PHONY : fclean clean all re
