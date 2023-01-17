# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 19:45:58 by gyopark           #+#    #+#              #
#    Updated: 2023/01/17 13:42:14 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror 
MLX			= -L./mlx -lmlx -framework OpenGL -framework AppKit
FT_PRINTF	= ft_printf
PRINTF_LIB	= libftprintf.a

SRCS 		= so_long1.c							\
			  so_long2.c							\
			  so_long3.c							\
			  gnl/get_next_line.c					\
			  gnl/get_next_line_utils.c	

OBJS 		= ${SRCS:.c=.o}

$(NAME) : $(OBJS)
		make all -C $(FT_PRINTF)
		cp $(FT_PRINTF)/$(PRINTF_LIB) ../$(NAME)
		$(CC) -o $@ $(MLX) $(PRINTF_LIB) $(OBJS)	

all : $(NAME)

fclean : clean
		rm -f $(NAME)
		make fclean -C $(FT_PRINTF)

clean :
		rm -f $(OBJS)
		make clean -C $(FT_PRINTF)

re : 
	make fclean 
	make all

.PHONY : fclean clean all re

