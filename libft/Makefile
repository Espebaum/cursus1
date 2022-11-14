# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 17:16:36 by gyopark           #+#    #+#              #
#    Updated: 2022/11/14 20:19:43 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = ft_atoi.c		\
	   ft_bzero.c		\
	   ft_calloc.c		\
	   ft_isalnum.c		\
	   ft_isalpha.c		\
	   ft_isascii.c		\
	   ft_isdigit.c		\
	   ft_isprint.c		\
	   ft_itoa.c		\
	   ft_memchr.c		\
	   ft_memcmp.c		\
	   ft_memcpy.c		\
	   ft_memmove.c		\
	   ft_memset.c		\
	   ft_putchar_fd.c	\
	   ft_putendl_fd.c	\
	   ft_putnbr_fd.c	\
	   ft_putstr_fd.c	\
	   ft_split.c		\
	   ft_strchr.c		\
	   ft_strdup.c		\
	   ft_striteri.c	\
	   ft_strjoin.c		\
	   ft_strlcat.c		\
	   ft_strlcpy.c		\
	   ft_strlen.c		\
	   ft_strmapi.c		\
	   ft_strncmp.c		\
	   ft_strnstr.c		\
	   ft_strrchr.c		\
	   ft_strtrim.c		\
	   ft_substr.c		\
	   ft_tolower.c		\
	   ft_toupper.c

SRC_BONUS = ft_lstnew.c	

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRC_BONUS:.c=.o}

ifdef WITH_BONUS
	OBJ = $(OBJS) $(OBJS_BONUS)
else
	OBJ = $(OBJS)
endif

all : ${NAME}

$(NAME): ${OBJ}
	ar -rcs $@ $^

bonus:
	make WITH_BONUS=1 ${NAME}

clean:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean bonus re 

