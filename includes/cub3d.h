/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:54:28 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/23 21:54:01 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include "parsing.h"

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
	t_pos		po;
	t_pos_fl	pl;
}					t_mlx;


void			ft_init_mlx(t_mlx m);
void			draw_pixel(t_img *ref, t_pos pos, unsigned char color[4], t_mlx m);
t_img			*create_new_img(t_mlx *m, t_img *ptr, int width, int height);
#endif