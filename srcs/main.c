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

int	main()
{
	create_application(create_vector2(840, 680), "Yolo gros code (c)");

	clear_screen();

	draw_rectangle(create_vector2(50, 50), create_vector2(150, 150), create_color(255, 0, 0, 255));
	draw_rectangle(create_vector2(75, 150), create_vector2(150, 50), create_color(0, 0, 255, 255));

	render_screen();

	return (run_application());
}
