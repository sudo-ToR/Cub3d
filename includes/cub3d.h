/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:54:28 by lnoirot           #+#    #+#             */
/*   Updated: 2020/04/21 11:22:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <math.h>
# include "parsing.h"

# define X11_KEY_PRESS          2
# define X11_KEY_PRESS_M        1
# define X11_KEY_RELEASE        3
# define X11_KEY_RELEASE_M      2


typedef struct		s_img
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*img;
	void	*ref;
	int		w;
	int		h;
	int		x;
	int		y;
}					t_img;

typedef struct		s_colors
{
	char floor[3];
	char ceil[3];
}					t_colors;

typedef struct		s_pos
{
	int x;
	int y;
}					t_pos;

typedef struct		s_pos_fl
{
	double x;
	double y;
}					t_pos_fl;

typedef	struct		s_ray
{
	t_pos_fl	coord;
	int			dir_wall;
	t_pos_fl	wall_coord;
}					t_ray;

typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_img		minimap;
	int			aff_minimap;
	t_img		render;
	t_img		no_text;
	t_img		so_text;
	t_img		ea_text;
	t_img		we_text;
	t_ray		ray;
	t_pos_fl	coord_vert;
	t_pos_fl	coord_hor;
	t_pars		p;
	t_colors	colors;
	t_pos		po;
	t_pos_fl	pl;
	double		cam_angle;
	double		ray_angle;
}					t_mlx;

# include "image.h"

void			set_color(t_mlx *m);
int				ft_init_mlx(t_mlx *m);
void			init_dir_vector(char v, double *cam_angle);
void			get_initial_position(char *v, t_pars p, t_pos_fl *pl);
char			*get_pixel_texture(t_img *texture, t_pos coord);
void			select_texture(t_img **texture, t_mlx *m);

#endif