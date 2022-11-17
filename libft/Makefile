# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 17:16:36 by gyopark           #+#    #+#              #
#    Updated: 2022/11/17 15:44:36 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS_MAN = ft_atoi.c		\
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

SRCS_BONUS = ft_lstnew.c		\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c

OBJS_MAN = $(SRCS_MAN:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME): $(OBJS_MAN) libft.h
	ar rc $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all bonus:
	rm -f all bonus $(NAME)
	ar rc $(NAME) $^
	touch $@

all: $(SRCS_MAN:.c=.o)

bonus: $(SRCS_BONUS:.c=.o)

clean:
	rm -f $(OBJS_MAN) $(OBJS_BONUS) all bonus

fclean: clean
	rm -f $(NAME)

re : 
	make fclean 
	make all

.PHONY : clean fclean re 
