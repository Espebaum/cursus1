# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:54:22 by gyopark           #+#    #+#              #
#    Updated: 2023/02/20 13:54:41 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT			= libft
LIBFT_LIB		= libft.a

RLFLAGS			= -lreadline
LDFLAGS			= -L${HOME}/.brew/opt/readline/lib
CPPFLAGS		= -I${HOME}/.brew/opt/readline/include

SRCS			=	main.c							\
					builtin/built_in_cd.c			\
					builtin/built_in_echo.c			\
					builtin/built_in_env.c			\
					builtin/built_in_exit1.c		\
					builtin/built_in_exit2.c		\
					builtin/built_in_export1.c		\
					builtin/built_in_export2.c		\
					builtin/built_in1.c				\
					builtin/envp_utils.c			\
					doc_parse/parsing_y1.c			\
					doc_parse/parsing_y2.c			\
					doc_parse/parsing_y3.c			\
					doc_parse/parsing_y4.c			\
					doc_parse/parsing_y5.c			\
					doc_parse/parsing_y6.c			\
					get_next_line/get_next_line.c	\
					pipes_youngski/check_cmd.c		\
					pipes_youngski/pipe_line1.c		\
					pipes_youngski/pipe_line2.c		\
					pipes_youngski/pipe_line3.c		\
					pipes_youngski/pipe_line4.c		\
					pipes_youngski/pipe_line5.c		\
					srcs/doc_open1.c				\
					srcs/doc_open2.c				\
					srcs/doc_open3.c				\
					srcs/doc_syntax1.c				\
					srcs/doc_syntax2.c				\
					srcs/err_exit.c					\
					srcs/init_1.c					\
					srcs/init_2.c					\
					srcs/lex_env1.c					\
					srcs/lex_env2.c					\
					srcs/lex_env3.c					\
					srcs/lex_free.c					\
					srcs/lex_make_push.c			\
					srcs/lex_read1.c				\
					srcs/lex_read2.c				\
					srcs/lex_tokenize.c				\
					srcs/lex_tokenize2.c			\
					srcs/sig_handle.c				\
					srcs/syntax_check1.c			\
					srcs/syntax_check2.c			\
					srcs/utils.c

OBJS			= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	make all -C $(LIBFT)
	$(CC) $(CFLAGS) $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS) $(OBJS) -o $@ $(LIBFT)/$(LIBFT_LIB)

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
