# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2020/02/28 19:56:49 by lnoirot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

NAME	=	Cub3D 
CC		= 	gcc -lmlx -framework OpenGL -framework AppKit
CFLAGS	= 	-g3 $(INCLUDES)

LIBFT_PATH = ./Libft
OBJ_PATH =	./obj/
LIBFT_MAKE = @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INC = -I $(LIBFT_PATH)
LIBFT_LIB = -L$(LIBFT_PATH) -lft
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
INCLUDES =  $(LIBFT_INC) -I$(LIBFT_PATH) -I./includes

SRCS_PATH = srcs
SRC_LIST =	main.c \
			parsing.c \
			parsing_utils.c \
			check_parsing.c \
			mlx_init.c \
			images.c \
			initial_param.c \
			minimap.c \
			ray.c
SRCS =		$(addprefix $(SRCS_PATH), $(SRC_LIST))
OBJS	=	$(addprefix $(OBJ_PATH), $(SRC_LIST:.c=.o))


all :		libft
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBFT_LIB)  $(FT_PRINTF_LIB) -o $(NAME)

libft:
			$(LIBFT_MAKE)

$(OBJ_PATH)%.o:		$(SRCS_PATH)/%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	$(LIBFT_MAKE) fclean
	rm -f $(NAME)

re : 		fclean all	

.PHONY:		all clean fclean re libft
