# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 12:12:45 by lnoirot           #+#    #+#              #
#    Updated: 2020/12/28 16:39:23 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

NAME	=	Cub3D 
CC		= 	clang
CFLAGS	= 	-Wall -Wextra -Werror -g3 $(INCLUDES)
LIBS	=  -L./mlx -lmlx -lbsd -lm -lXext -lX11
# LIBS	= -lmlx -L$(LIBFT_PATH) -lft -framework OpenGL -framework Appkit

LIBFT_PATH = ./Libft
OBJ_PATH =	./obj/
LIBFT_MAKE = @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INC = -I $(LIBFT_PATH)
LIBFT_LIB = -L$(LIBFT_PATH) -lft
FT_PRINTF_LIB = -L$(LIBFT_PATH)/ft_printf -lftprintf
MLX_PATH = ./mlx
MLX_MAKE = @$(MAKE) -C $(MLX_PATH) 
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
			ray.c \
			textures.c \
			sprites.c \
			sprites_utils.c \
			screenshot.c \
			utils.c \
			parsing_utils_bis.c
SRCS =		$(addprefix $(SRCS_PATH), $(SRC_LIST))
OBJS	=	$(addprefix $(OBJ_PATH), $(SRC_LIST:.c=.o))


all :		libft
			@mkdir -p ./obj
			@$(MLX_MAKE)
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBS) $(LIBFT_LIB)  $(FT_PRINTF_LIB) -o $(NAME)

libft:
			$(LIBFT_MAKE)

$(OBJ_PATH)%.o:		$(SRCS_PATH)/%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	$(LIBFT_MAKE) fclean
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)

re : 		fclean all	

.PHONY:		all clean fclean re libft
