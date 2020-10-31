/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/05/18 16:36:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_cam_angle(double *angle)
{
	if (*angle > 2.0 * M_PI)
		*angle -= 2.0 * M_PI;
	if (*angle < 0.)
		*angle += 2.0 * M_PI;
}

void	move(t_pos_fl step, t_mlx *m, double rota)
{
	t_pos_fl	new_coord;

	new_coord.x = m->pl.x + step.x * sin(m->cam_angle + rota);
	new_coord.y = m->pl.y + step.y * cos(m->cam_angle + rota);
	if (m->p.map[(int)new_coord.y][(int)new_coord.x] != '1')
	{
		m->pl.x = new_coord.x;
		m->pl.y = new_coord.y;
	}
}

int		exit_game(t_mlx *m)
{
	mlx_destroy_window(m->mlx_ptr, m->win_ptr);
	m->win_ptr = NULL;
	mlx_destroy_image(m->mlx_ptr, m->minimap.ref);
	mlx_destroy_image(m->mlx_ptr, m->render.ref);
	mlx_destroy_image(m->mlx_ptr, m->no_text.ref);
	mlx_destroy_image(m->mlx_ptr, m->so_text.ref);
	mlx_destroy_image(m->mlx_ptr, m->ea_text.ref);
	mlx_destroy_image(m->mlx_ptr, m->we_text.ref);
	m->mlx_ptr = NULL;
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_mlx		*m;
	double		coeff;

	m = (t_mlx *)param;
	adjust_cam_angle(&m->cam_angle);
	coeff = tan(m->cam_angle);
	if (keycode == 109)
		m->aff_minimap = (m->aff_minimap) ? 0 : 1;
	if (keycode == 100)
		m->cam_angle += 0.1;
	if (keycode == 97)
		m->cam_angle -= 0.1;
	if (keycode == 65362 || keycode == 119)
		move((t_pos_fl) {0.1, -0.1}, m, M_PI_2);
	if (keycode == 65364 || keycode == 115)
		move((t_pos_fl) {-0.1, 0.1}, m, M_PI_2);
	if (keycode == 65363)
		move((t_pos_fl) {-0.1, 0.1}, m, 0.);
	if (keycode == 65361)
		move((t_pos_fl) {0.1, -0.1}, m, 0.);
	if (keycode == 65307 || keycode == 113)
		exit(exit_game(m));
	return (0);
}

int		game_loop(void *param)
{
	t_mlx		*m;

	m = (t_mlx *)param;
	if (m->aff_minimap)
		minimap(m);
	draw_image(m->cam_angle, m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->render.ref, 0, 0);
	if (m->aff_minimap)
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->minimap.ref, 25, 25);
	return (1);
}

int		ft_init_mlx(t_mlx *m)
{
	char	v;

	set_color(m);
	get_initial_position(&v, m->p, &m->pl);
	init_dir_vector(v, &m->cam_angle);
	m->mlx_ptr = mlx_init();
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
	m->win_ptr = mlx_new_window(m->mlx_ptr, m->p.r[0], m->p.r[1], "Cub3D");
	if (!create_new_img(m, &m->render, m->p.r[0], m->p.r[1]))
		return (1);
	if (!create_new_img(m, &m->minimap, m->p.width * 16, m->p.height * 16))
		return (1);
	mlx_hook(m->win_ptr, X11_KEY_PRESS, X11_KEY_PRESS_M, key_press, m);
	mlx_loop_hook(m->mlx_ptr, game_loop, m);
	mlx_loop(m->mlx_ptr);
	return (0);
}
