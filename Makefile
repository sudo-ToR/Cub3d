NAME = cub3d

CC = gcc

## --- Description des dossiers du projet ---
# la liste de tout les dossiers ou on peut trouver un .c
SRC_DIR = $(shell find srcs -type d)

# la liste de tout les dossiers ou on peut trouver un .h
INC_DIR = $(shell find includes -type d)

# la liste de tout les dossiers ou on peut trouver un .o
OBJ_DIR = obj

# la liste de tout les dossiers ou on peut trouver un .a
LIB_DIR = $(shell find lib -type d)


## --- Definition des Vpath
vpath %.c $(foreach dir, $(SRC_DIR), $(dir): )


## --- Definition des objets
# la liste des .c a compiler pour notre projet
SRC = main.c t_application.c t_application_handle_screen.c t_application_run.c t_color.c t_vector.c draw_primitive.c

# la liste des .o a utiliser pour notre projet
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

## --- Definition des librairies de dependance
LIB = mlx ft

## -- Definition des flags de compilation/includes/linkage
# les flags de compilation
CFLAGS = -Wall -Wextra -Werror

# les flags d'includes
IFLAGS = $(foreach dir, $(INC_DIR),-I $(dir) )

# les flags de librarie (les flags de linkage)
LFLAGS = $(foreach dir, $(LIB_DIR),-L $(dir) ) $(foreach lib, $(LIB),-l $(lib) ) -framework AppKit -framework OpenGL

all :
	make $(NAME)

$(OBJ_DIR)/%.o : %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean:
	make clean
	rm -rf $(NAME)

re:
	make fclean
	make $(NAME)

## regle pour compiler les differentes libraries dans lib
install :
	@make -C lib/libft
	@make -C lib/mlx

re-install :
	@make -C lib/libft re
	@make -C lib/mlx re

show:
	@echo "SRCS :\n$(SRC)\n"
	@echo "OBJS :\n$(OBJ)\n"
	@echo "CFLAGS :\n$(CFLAGS)\n"
	@echo "IFLAGS :\n$(IFLAGS)\n"
	@echo "LFLAGS :\n$(LFLAGS)\n"
