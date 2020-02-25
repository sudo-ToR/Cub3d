# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2020/02/15 13:54:46 by lnoirot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES :

NAME	= libft.a

GNL_PATH =	./gnl
IS_PATH =	./is_something
STR_PATH =	./str
AFF_PAH =	./affichage
MEM_PATH =	./mem
MATHS_PATH =	./maths

SRCS	=	$(GNL_PATH)/get_next_line.c \
		$(GNL_PATH)/get_next_line_utils.c \
		$(MEM_PATH)/ft_bzero.c \
		$(MEM_PATH)/ft_memset.c \
		$(MEM_PATH)/ft_memcpy.c \
		$(MEM_PATH)/ft_memccpy.c \
		$(MEM_PATH)/ft_memmove.c \
		$(MEM_PATH)/ft_memchr.c \
		$(MEM_PATH)/ft_memcmp.c \
		$(STR_PATH)/ft_strlen.c \
		$(IS_PATH)/ft_isalpha.c \
		$(IS_PATH)/ft_isdigit.c \
		$(IS_PATH)/ft_isalnum.c \
		$(IS_PATH)/ft_isascii.c \
		$(IS_PATH)/ft_isprint.c \
		$(IS_PATH)/ft_toupper.c \
		$(IS_PATH)/ft_tolower.c \
		$(STR_PATH)/ft_strchr.c \
		$(STR_PATH)/ft_strrchr.c \
		$(STR_PATH)/ft_strncmp.c \
		$(STR_PATH)/ft_strlcpy.c \
		$(STR_PATH)/ft_strlcat.c \
		$(STR_PATH)/ft_strnstr.c \
		$(MATHS_PATH)/ft_atoi.c \
		$(MEM_PATH)/ft_calloc.c \
		$(STR_PATH)/ft_strdup.c \
		$(STR_PATH)/ft_substr.c \
		$(STR_PATH)/ft_strjoin.c \
		$(STR_PATH)/ft_strtrim.c \
		$(STR_PATH)/ft_split.c \
		$(MATHS_PATH)/ft_itoa.c \
		$(STR_PATH)/ft_strmapi.c \
		$(AFF_PAH)/ft_putchar_fd.c \
		$(AFF_PAH)/ft_putstr_fd.c \
		$(AFF_PAH)/ft_putendl_fd.c \
		$(AFF_PAH)/ft_putnbr_fd.c \
		$(STR_PATH)/ft_strcmp.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g  -Iincludes


%.o:	%.c		
	$(CC) $(CFLAGS) -c $< -o $@

all :		$(NAME)

$(NAME):	$(OBJS) 
			ar rc $(NAME) $(OBJS)
			make -C ./ft_printf


clean :
			rm -f $(OBJS)
			make fclean -C ./ft_printf

fclean :	clean
			rm -f $(NAME)
			make  fclean -C ./ft_printf 

re : fclean all	
	$(MAKE) re -C ./ft_printf


.PHONY:		all clean fclean re
