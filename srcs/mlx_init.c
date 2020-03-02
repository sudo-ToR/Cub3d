/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/02 21:38:31 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, void *param)
{
	t_mlx 		*m;
	t_pos_fl	new_coord;
	double		coeff;

	m = (t_mlx *)param;
	printf("%f\n", m->cam_angle);
	if (m->cam_angle > 2.0 * M_PI)
		m->cam_angle -= 2.0 * M_PI;
	coeff = tan(m->cam_angle);
	if (keycode == 13 || keycode == 126)
	{
		new_coord.y = (m->cam_angle > 0 && m->cam_angle < M_PI) ? m->pl.y + 0.5 : m->pl.y - 0.5;
		new_coord.x = (m->cam_angle == M_PI_2 || m->cam_angle == 3 * M_PI_2) ? m->pl.x: m->pl.x - 0.5 / coeff;
		if (m->p.map[(int)new_coord.y][(int)new_coord.x] == '0')
		{
			m->pl.x = new_coord.x;
			m->pl.y = new_coord.y;
		}
	}
	if (keycode == 1 || keycode == 125)
	{
		new_coord.y = (m->cam_angle > 0 && m->cam_angle < M_PI) ? m->pl.y - 0.5 : m->pl.y + 0.5;
		new_coord.x = (m->cam_angle == M_PI_2 || m->cam_angle == 3 * M_PI_2) ? m->pl.x : m->pl.x + 0.5 / coeff;
		if (m->p.map[(int)new_coord.y][(int)new_coord.x] == '0')
		{
			m->pl.x = new_coord.x;
			m->pl.y = new_coord.y;
		}
	}
	if (keycode == 0)
	{
		new_coord.x = ((m->cam_angle > 0 && m->cam_angle < M_PI_2) 
			|| (m->cam_angle > 3. * M_PI_2  && m->cam_angle < 2. * M_PI_2)) ? m->pl.x + 0.5 : m->pl.x - 0.5;
		new_coord.y = (m->cam_angle == 0 || m->cam_angle == M_PI) ? m->pl.y : m->pl.x + 0.5 * coeff;
		if (m->p.map[(int)new_coord.y][(int)new_coord.x] == '0')
		{
			m->pl.x = new_coord.x;
			m->pl.y = new_coord.y;
		}
	}
	if (keycode == 2)
	{
			m->pl.x += (m->pl.x < m->p.width + 1.5 && m->p.map[(int)(m->pl.y)][(int)(m->pl.x + 0.5)] == '0') ? 0.5 : 0; 
	}
	if (keycode == 124)
	{
		m->cam_angle += 0.1;
	}
	if (keycode == 123)
	{
		m->cam_angle -= 0.1; 
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
