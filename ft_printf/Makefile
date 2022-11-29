# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/27 16:18:37 by gyopark           #+#    #+#              #
#    Updated: 2022/11/29 21:19:33 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT		= libft
LIBFT_LIB	= libft.a

SRCS 		= ft_printf.c				\
			  ft_printf_cs.c			\
			  ft_printf_diu.c			\
			  ft_printf_pxX.c			\
			  ft_change_hexa.c			\
			  ft_change_hexa_address.c

OBJS 		= ${SRCS:.c=.o}

$(NAME) : $(OBJS)
		make all -C $(LIBFT)/
		cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
		ar rcs $(NAME) $(OBJS)

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

.PHONY : fclean clean all re 
