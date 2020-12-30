/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:32:27 by lnoirot           #+#    #+#             */
/*   Updated: 2020/12/30 17:10:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <stdio.h>
# include "../Libft/libft.h"
# include "../Libft/ft_printf/ft_printf.h"
# include <sys/errno.h>
# include <string.h>

typedef struct		s_pars
{
	char			*no;
	char			*so;
	char			*s;
	char			*we;
	char			*ea;
	int				*r;
	int				*f;
	int				*c;
	char			**map;
	int				width;
	int				height;
	char			start_dir;
}					t_pars;

typedef enum		e_parsing_error
{
	SUCCESS,
	WRONG_RESOLUTION,
	WRONG_PATH_CUB_FILE,
	WRONG_TEXTURE,
	WRONG_ARG,
	WRONG_C,
	WRONG_F,
	WRONG_MAP,
	DUPLICATION_ARGUMENT
}					t_parsing_error;

int					clean_texture(char *line, char **texture);
int					is_texture(char *line);
int					clean_num(char *line, int id, int **res);
int					ft_clean_map(char **map, int nbr_line);
int					check_char_map(char **map, int nbr_line);
void				ft_swap(int *color);
int					ft_isspace(char c);
void				ft_realloc(int *nbr_line, char ***map, char *line);
void				cut_space(t_pars *p);
void				free_clean_num(char **stock, char *line);
void				square_map(t_pars *p);
int					count_arg(char *line, int id);
int					check_clean_num(int **res, int id, char *line);
int					is_map(char *line);
void				clean_num_moulinette(char **texture);
#endif
