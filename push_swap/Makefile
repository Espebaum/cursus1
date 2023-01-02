# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 16:22:02 by gyopark           #+#    #+#              #
#    Updated: 2023/01/01 20:27:39 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
CHECKER		= checker

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS_MAN	= push_swap.c			\
			  push_swap_cmd1.c		\
			  push_swap_cmd2.c		\
			  push_swap_cmd3.c		\
			  push_swap_deque1.c	\
			  push_swap_deque2.c	\
			  push_swap_deque3.c	\
			  push_swap_hard1.c		\
			  push_swap_merge1.c	\
			  push_swap_sort1.c		\
			  push_swap_sort2.c		\
			  push_swap_sort3.c		\
			  push_swap_sort4.c		\
			  push_swap_utils1.c	\
			  push_swap_utils2.c	\
			  ft_split.c			\
			  ft_split_utils.c		

SRCS_BONUS	= checkers/checker.c				\
			  checkers/check_cmd1.c				\
			  checkers/check_cmd2.c				\
			  checkers/checker_cmd1.c			\
			  checkers/checker_cmd2.c			\
			  checkers/checker_cmd3.c			\
			  checkers/checker_deque1.c			\
			  checkers/checker_deque2.c			\
			  checkers/checker_deque3.c			\
			  checkers/checker_utils1.c			\
			  checkers/ft_split_checker.c		\
			  checkers/ft_split_utils_checker.c	\
			  checkers/get_next_line.c			\
			  checkers/get_next_line_utils.c

OBJS_MAN		= $(SRCS_MAN:.c=.o)

OBJS_BONUS		= $(SRCS_BONUS:.c=.o)

$(NAME) : $(OBJS_MAN)
		$(CC) -o $@ $(OBJS_MAN)

$(CHECKER) : $(OBJS_BONUS)
		$(CC) -o $@ $(OBJS_BONUS)

all : $(NAME)

bonus : $(CHECKER)

fclean : clean
		rm -f $(NAME) $(CHECKER)

clean :
		rm -f $(OBJS_MAN) $(OBJS_BONUS)

re :
	make fclean
	make all

.PHONY : fclean clean all re bonus
