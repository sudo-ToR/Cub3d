/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/04 16:50:42 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		new_coord.y = (coeff * pow(step, 2)) / sqrt(1 + pow(coeff, 2));
		printf("x = %f\ty = %f\n=======>%f\n",m->pl.x, m->pl.y, new_coord.y);
		m->pl.y += copysign(new_coord.y, coeff);
		m->pl.x += (coeff) ? new_coord.y / coeff : 0;
	}
	minimap(m, m->cam_angle);
	draw_image(m->cam_angle, m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->render.ref, 0, 0);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->minimap.ref, 25, 25);
	return (0);
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
	minimap(m, m->cam_angle);
	draw_image(m->cam_angle, m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->render.ref, 0, 0);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->minimap.ref, 25, 25);
	mlx_hook(m->win_ptr, X11_KEY_PRESS, X11_KEY_PRESS_M, key_press, m);
	mlx_loop(m->mlx_ptr);
}
