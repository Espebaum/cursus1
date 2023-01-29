# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:54:22 by gyopark           #+#    #+#              #
#    Updated: 2023/01/29 12:21:40 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
CFLAGS			= -wall -wextra -werror

LIBFT			= libft
LIBFT_LIB		= libft.a

RLFLAGS			= -lreadline
LIBFLAGS		= -L/Users/gyopark/.brew/opt/readline/lib
INCFLAGS		= -I/Users/gyopark/.brew/opt/readline/include

SRCS			= main.c 

OBJS			= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	make bonus -C $(LIBFT)
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	$(CC) $(CFLAGS) $(RLFLAGS) $(LIBFLAGS) &(INCFLAGS) $(OBJS) -o $@

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
