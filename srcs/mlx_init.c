/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/28 13:34:53 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void
	ft_init_mlx(t_mlx m)
{
	char	v;

	get_initial_position(&v, m.p, &m.pl);
	init_dir_vector(v, &m.cam_angle);
	m.mlx_ptr = mlx_init();
	m.win_ptr = mlx_new_window(m.mlx_ptr, m.p.r[0], m.p.r[1], "Cub3D");
	create_new_img(&m, &m.render, m.p.r[0], m.p.r[1]);
	create_new_img(&m, &m.minimap, m.p.width * 17, m.p.height * 17);
	minimap(m, m.cam_angle);
	draw_image(m.cam_angle, m);
	mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.render.ref, 0, 0);
	mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.minimap.ref, 50, 50);
	mlx_loop(m.mlx_ptr);
}
