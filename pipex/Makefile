# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 21:14:18 by gyopark           #+#    #+#              #
#    Updated: 2023/01/04 21:28:31 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT		= libft
LIBFT_LIB	= libft.a

SRCS 		= pipex.c				\
			  pipex2.c
		

OBJS 		= ${SRCS:.c=.o}

$(NAME) : $(OBJS)
		make all -C $(LIBFT)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)/$(LIBFT_LIB)


all : $(NAME)

fclean : clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)

clean :
		rm -f $(OBJS)
		make clean -C $(LIBFT)

re : 
	make fclean 
	make all

.PHONY : fclean clean all re libft
