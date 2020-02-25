# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2020/02/15 11:28:20 by lnoirot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

NAME	= libftprintf.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I.


SRCS	=	basic_functions.c \
		ft_printf.c \
		basics_functions_1.c \
		ft_count.c \
		converter_functions.c \
		converter_utils.c \
		converter_utils_1.c 

OBJS	=	$(SRCS:.c=.o)

all :		$(NAME)

$(NAME):	$(OBJS)
	ar rc $@ $^

%.o:	%.c
	$(CC) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean :	clean
	rm -f $(NAME)

re : fclean all	

.PHONY:		all clean fclean re
