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

void put_pixel(t_vector2 pos, t_color color)
{
	size_t actual_pixel;

	actual_pixel = pos.x * 4 + pos.y * g_app.size_line;
	g_app.pixels[actual_pixel + RED_COMP] = color.r; // red component
	g_app.pixels[actual_pixel + GREEN_COMP] = color.g; // green component
	g_app.pixels[actual_pixel + BLUE_COMP] = color.b; // blue component
	g_app.pixels[actual_pixel + ALPHA_COMP] = 100 - (color.a * 100 / 255); // alpha component
}

void clear_screen()
{
	int x;
	int y;

	x = 0;
	while (x < g_app.size.x)
	{
		y = 0;
		while (y < g_app.size.y)
		{
			put_pixel(create_vector2(x, y), g_app.background);
			y++;
		}
		x++;
	}
}

void render_screen()
{
	mlx_put_image_to_window(g_app.mlx_ptr, g_app.win_ptr, g_app.img_ptr, 0, 0);
}
