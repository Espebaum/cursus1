# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 21:14:18 by gyopark           #+#    #+#              #
#    Updated: 2023/01/05 22:55:05 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT		= libft
LIBFT_LIB	= libft.a

SRCS_MAN	= pipex1.c				\
			  pipex2.c				\
			  pipex_utils.c

SRCS_BONUS	= pipex_bonus1.c		\
			  pipex_bonus2.c		\
			  pipex_bonus_utils.c

OBJS_MAN 	= ${SRCS_MAN:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

all bonus:
		rm -f all bonus $(NAME)
		make fclean -C $(LIBFT)
		make all -C $(LIBFT) 
		$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBFT)/$(LIBFT_LIB)
		touch $@

all : $(OBJS_MAN)

bonus : $(OBJS_MAN) $(OBJS_BONUS)

fclean : clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)

clean :
		rm -f $(OBJS_MAN) $(OBJS_BONUS) all bonus
		make clean -C $(LIBFT)

re : 
	make fclean 
	make all

.PHONY : fclean clean re libft
