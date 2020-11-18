/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:32:27 by lnoirot           #+#    #+#             */
/*   Updated: 2020/11/18 20:47:04 by user42           ###   ########.fr       */
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

# define WIDTH_MAX 2560
# define HEIGHT_MAX 1440

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
	WRONG_MAP
}					t_parsing_error;

int					is_texture(char *line);
void				clean_texture(char *line, char **texture);
void				clean_num(char *line, int id, int **res);
void				get_texture(t_pars *p, char *line);
int					ft_pars(int fd, t_pars *p);
int					ft_clean_map(char **map, int nbr_line);
int					ft_check_parsing(t_pars *p, int fd);
int					aff_error(int error);
int					check_char_map(char c);
void				ft_swap(int *color);

#endif
