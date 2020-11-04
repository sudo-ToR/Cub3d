/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:29:22 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 15:49:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H

# define STRUCTURES_H

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
	double				angle;
}						t_sprites;

typedef	struct			s_coord_sprite
{
	t_pos_fl			column;
	t_pos_fl			lines;
}						t_coord_sprite;

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

#endif