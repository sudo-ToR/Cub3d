# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2020/02/27 11:45:14 by lnoirot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

NAME	=	Cub3D 
CC		= 	gcc -lmlx -framework OpenGL -framework AppKit
CFLAGS	= 	-g3 $(INCLUDES)

LIBFT_PATH = ./Libft
LIBFT_MAKE = @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INC = -I $(LIBFT_PATH)
LIBFT_LIB = -L$(LIBFT_PATH) -lft
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
INCLUDES =  $(LIBFT_INC) -I$(LIBFT_PATH) -I./includes

SRCS_PATH = ./srcs
SRCS	=	$(SRCS_PATH)/main.c \
			$(SRCS_PATH)/parsing.c \
			$(SRCS_PATH)/parsing_utils.c \
			$(SRCS_PATH)/check_parsing.c \
			$(SRCS_PATH)/mlx_init.c \
			$(SRCS_PATH)/images.c \
			$(SRCS_PATH)/initial_pos.c \
			$(SRCS_PATH)/minimap.c
OBJS	=	$(SRCS:.c=.o)


all :		libft
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBFT_LIB)  $(FT_PRINTF_LIB) -o $(NAME)

libft:
			$(LIBFT_MAKE)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	$(LIBFT_MAKE) fclean
	rm -f $(NAME)

re : 		fclean all	

.PHONY:		all clean fclean re libft
