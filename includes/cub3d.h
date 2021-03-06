/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:54:28 by lnoirot           #+#    #+#             */
/*   Updated: 2021/01/02 21:52:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <math.h>
# include "parsing.h"
# include "../Libft/libft.h"
# include <float.h>
# include "structures.h"
# include "image.h"
# include "sprites.h"
# include <sys/types.h>
# include <fcntl.h>
# include "screenshot.h"

# define X11_KEY_PRESS          2
# define X11_KEY_PRESS_M        1
# define X11_KEY_RELEASE        3
# define X11_KEY_RELEASE_M      2
# define W 65362
# define ARR_UP 119
# define S 65364
# define ARR_DOWN 115
# define D 65363
# define A 65361
# define ARR_RIGHT 100
# define ARR_LEFT 97
# define ESC 65307
# define Q 113
# define M 109

void			set_color(t_mlx *m);
int				ft_init_mlx(t_mlx *m);
void			init_dir_vector(char v, double *cam_angle);
void			get_initial_position(char *v, t_pars p, t_pos_fl *pl);
char			*get_pixel_texture(t_img *texture, t_pos coord);
void			select_texture(t_img **texture, t_mlx *m);
void			loop_win(t_mlx *m);
int				exit_game(t_mlx *m, int mode);
void			adjust_cam_angle(double *angle);
int				get_texture(t_pars *p, char *line, t_mlx *m);
int				ft_check_parsing(t_pars *p, t_mlx *m);
int				ft_pars(int fd, t_pars *p, t_mlx *m);
int				aff_error(int error, t_mlx *m);
int				error_dupplication_text(char *line, char **text, t_mlx *m);
int				ft_pars_num(char *line, t_pars *p);
void			ft_pars_utils_map(int ret, char *line, t_pars *p);
int				ft_isnum(char *line);
void			find_map_width(t_pars *p);
int				empty_line_parsing(char *line, t_pars *p, t_mlx *m);
void			wrong_arg(char *line, t_mlx *m);
#endif
