/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/11/29 18:24:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_pos_fl step, t_mlx *m, double rota)
{
	t_pos_fl	new_coord;

	new_coord.x = m->pl.x + step.x * sin(m->cam_angle + rota);
	new_coord.y = m->pl.y + step.y * cos(m->cam_angle + rota);
	if (m->p.map[(int)new_coord.y][(int)new_coord.x] == '0')
	{
		m->pl.x = new_coord.x;
		m->pl.y = new_coord.y;
	}
}

int		key_press(int keycode, void *param)
{
	t_mlx		*m;
	double		coeff;

	m = (t_mlx *)param;
	adjust_cam_angle(&m->cam_angle);
	coeff = tan(m->cam_angle);
	if (keycode == M)
		m->aff_minimap = (m->aff_minimap) ? 0 : 1;
	if (keycode == ARR_RIGHT)
		m->cam_angle += 0.1;
	if (keycode == ARR_LEFT)
		m->cam_angle -= 0.1;
	if (keycode == W || keycode == ARR_UP)
		move((t_pos_fl) {0.1, -0.1}, m, M_PI_2);
	if (keycode == S || keycode == ARR_DOWN)
		move((t_pos_fl) {-0.1, 0.1}, m, M_PI_2);
	if (keycode == D)
		move((t_pos_fl) {-0.1, 0.1}, m, 0.);
	if (keycode == A)
		move((t_pos_fl) {0.1, -0.1}, m, 0.);
	if (keycode == ESC || keycode == Q)
		exit_game(m, 0);
	return (0);
}

int		game_loop(void *param)
{
	t_mlx		*m;

	m = (t_mlx *)param;
	minimap(m);
	draw_image(m->cam_angle, m);
	m->distance.i = 0;
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->render.ref, 0, 0);
	if (m->aff_minimap)
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->minimap.ref, 25, 25);
	return (1);
}

void	loop_win(t_mlx *m)
{
	m->win_ptr = mlx_new_window(m->mlx_ptr, m->p.r[0], m->p.r[1], "Cub3D");
	mlx_hook(m->win_ptr, X11_KEY_PRESS, X11_KEY_PRESS_M, key_press, m);
	mlx_hook(m->win_ptr, 17, 0, exit_game, m);
	mlx_loop_hook(m->mlx_ptr, game_loop, m);
	mlx_loop(m->mlx_ptr);
}

int		ft_init_mlx(t_mlx *m)
{
	char	v;

	set_color(m);
	get_initial_position(&v, m->p, &m->pl);
	init_dir_vector(v, &m->cam_angle);
	if (!(m->distance.distance = malloc(sizeof(double) * m->p.r[0])))
		return (1);
	m->distance.i = 0;
	m->mlx_ptr = mlx_init();
	m->sprites = NULL;
	if (!(create_text(m, &m->no_text, m->p.no)))
		return (1);
	if (!(create_text(m, &m->so_text, m->p.so)))
		return (1);
	if (!(create_text(m, &m->we_text, m->p.we)))
		return (1);
	if (!(create_text(m, &m->ea_text, m->p.ea)))
		return (1);
	if (!(create_text(m, &m->s_text, m->p.s)))
		return (1);
	if (!create_new_img(m, &m->render, m->p.r[0], m->p.r[1]))
		return (1);
	if (!create_new_img(m, &m->minimap, m->p.width * 16, m->p.height * 16))
		return (1);
	return (0);
}
