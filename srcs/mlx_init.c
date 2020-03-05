/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/05 20:22:17 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	n(){}

void	adjust_cam_angle(double *angle)
{
	if (*angle > 2.0 * M_PI)
		*angle -= 2.0 * M_PI;
	if (*angle < 0)
		*angle += 2.0 * M_PI;
}


int		key_press(int keycode, void *param)
{
	t_mlx 		*m;
	t_pos_fl	new_coord;
	double		coeff;
	double		step;

	m = (t_mlx *)param;
	step = 0.5;
	adjust_cam_angle(&m->cam_angle);
	coeff = tan(m->cam_angle);
	if (keycode == 124)
		m->cam_angle += 0.1;
	if (keycode == 123)
		m->cam_angle -= 0.1;
	if (keycode == 13 || keycode == 126)
	{
		/*new_coord.y = */m->pl.y -= step * cos(m->cam_angle + M_PI_2);
		/*new_coord.x = */m->pl.x += step * sin(m->cam_angle + M_PI_2);
	}
	if (keycode == 1 || keycode == 125)
	{
		/*new_coord.y = */m->pl.y += step * cos(m->cam_angle + M_PI_2);
		/*new_coord.x = */m->pl.x -= step * sin(m->cam_angle + M_PI_2);
	}
	if (keycode == 2)
	{
		/*new_coord.y = */m->pl.y += step * cos(m->cam_angle);
		/*new_coord.x = */m->pl.x -= step * sin(m->cam_angle);
	}
		if (keycode == 0)
	{
		/*new_coord.y = */m->pl.y -= step * cos(m->cam_angle);
		/*new_coord.x = */m->pl.x += step * sin(m->cam_angle);
	}
	return (0);
}

int		game_loop(void *param)
{
	t_mlx 		*m;

	m = (t_mlx *)param;
	minimap(m, m->cam_angle);
	draw_image(m->cam_angle, m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->render.ref, 0, 0);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->minimap.ref, 25, 25);
	return (1);
}

void	ft_init_mlx(t_mlx *m)
{
	char	v;

	set_color(m);
	get_initial_position(&v, m->p, &m->pl);
	init_dir_vector(v, &m->cam_angle);
	m->mlx_ptr = mlx_init();
	m->win_ptr = mlx_new_window(m->mlx_ptr, m->p.r[0], m->p.r[1], "Cub3D");
	create_new_img(m, &m->render, m->p.r[0], m->p.r[1]);
	create_new_img(m, &m->minimap, m->p.width * 16, m->p.height * 16);
	mlx_hook(m->win_ptr, X11_KEY_PRESS, X11_KEY_PRESS_M, key_press, m);
	mlx_loop_hook(m->mlx_ptr, game_loop, m);
	mlx_loop(m->mlx_ptr);
}
