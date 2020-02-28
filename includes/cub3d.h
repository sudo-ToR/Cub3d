/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:54:28 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/28 19:22:11 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include "parsing.h"
# include "move.h"




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
	unsigned char floor[3];
	unsigned char ceil[3];
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


typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_img		minimap;
	t_img		render;
	t_pars		p;
	t_colors	colors;
	t_pos		po;
	t_pos_fl	pl;
	t_pos_fl	inter;
	double		cam_angle;
}					t_mlx;

# include "image.h"

void			set_color(t_mlx *m);
void			ft_init_mlx(t_mlx *m);
void			init_dir_vector(char v, double *cam_angle);
void			get_initial_position(char *v, t_pars p, t_pos_fl *pl);

#endif