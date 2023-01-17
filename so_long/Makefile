# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 19:45:58 by gyopark           #+#    #+#              #
#    Updated: 2023/01/17 21:00:05 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror 
MLX			= -L./mlx -lmlx -framework OpenGL -framework AppKit
MLXDIR		= ./mlx
FT_PRINTF	= ft_printf
PRINTF_LIB	= libftprintf.a

SRCS_MAN 	= so_long1.c							\
			  so_long2.c							\
			  so_long3.c							\
			  gnl/get_next_line.c					\
			  gnl/get_next_line_utils.c	

SRCS_BONUS	= s_bonus/so_long1_bonus.c	\
			  s_bonus/so_long2_bonus.c	\
			  s_bonus/so_long3_bonus.c	\
			  gnl/get_next_line.c	\
			  gnl/get_next_line_utils.c

OBJS_MAN 	= ${SRCS_MAN:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

$(NAME) : all 

all bonus:
		rm -f all bonus $(NAME)
		make fclean -C $(FT_PRINTF)
		make all -C $(MLXDIR)	
		make all -C $(FT_PRINTF)
		$(CC) $(CFLAGS) -o $(NAME) $(MLX) $^ $(FT_PRINTF)/$(PRINTF_LIB)
		touch $@

all : $(OBJS_MAN)

bonus : $(OBJS_BONUS)

fclean : clean
		rm -f $(NAME)
		make fclean -C $(FT_PRINTF)

clean :
		rm -f $(OBJS_MAN) $(OBJS_BONUS) all bonus 
		make clean -C $(FT_PRINTF)
		make clean -C $(MLXDIR)

re : 
	make fclean 
	make all

.PHONY : fclean clean re ft_printf libft
