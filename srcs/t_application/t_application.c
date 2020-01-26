/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:29:31 by lnoirot           #+#    #+#             */
/*   Updated: 2020/01/26 16:55:07 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_application g_app;

void create_application(int size_x, int size_y, char *prog_name)
{
	g_app.mlx_ptr = mlx_init();
	g_app.size_x = size_x;
	g_app.size_y = size_y;
	g_app.win_ptr = mlx_new_window(g_app.mlx_ptr, g_app.size_x, g_app.size_y, prog_name);
	g_app.img_ptr = mlx_new_image(g_app.mlx_ptr, g_app.size_x, g_app.size_y);
	g_app.pixels = mlx_get_data_addr(g_app.img_ptr,
						&(g_app.bits_per_pixel),
						&(g_app.size_line),
						&(g_app.endian)
					);
	g_app.background = create_color(50, 50, 50, 255);
}

void destroy_application()
{
	mlx_destroy_window(g_app.mlx_ptr, g_app.win_ptr);
}
