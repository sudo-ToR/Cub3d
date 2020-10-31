/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:54:28 by lnoirot           #+#    #+#             */
/*   Updated: 2020/10/31 17:02:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <math.h>
# include "parsing.h"
#include "../Libft/libft.h"

# define X11_KEY_PRESS          2
# define X11_KEY_PRESS_M        1
# define X11_KEY_RELEASE        3
# define X11_KEY_RELEASE_M      2

// # define W 13
// # define ARR_UP 126
// # define S 1
// # define ARR_DOWN 125
// # define D 2
// # define A 0
// # define ARR_RIGHT 124
// # define ARR_LEFT 123
// # define ESC 53
// # define Q 12
// # define M 46

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

typedef struct			s_sprites
{
	t_pos_fl			coord;
	double				distance;
}						t_sprites;

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
	t_img		s_text;
	t_ray		ray;
	t_pos_fl	coord_vert;
	t_pos_fl	coord_hor;
	t_pars		p;
	t_colors	colors;
	t_pos		po;
	t_pos_fl	pl;
	t_list		*sprites;
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
void			get_sprites(t_mlx *m, t_pos_fl coord, double distance);

#endif