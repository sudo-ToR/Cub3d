/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:41:45 by user42            #+#    #+#             */
/*   Updated: 2020/11/18 20:13:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_int(int n, int fd)
{
	write(fd, &n, 4);
}

void	make_screenshot(t_mlx *m)
{
	int		fd;
	int		i;
	int		size;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	size = m->p.r[0] * m->p.r[1] * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size, sizeof(size));
	write_int(0, fd);
	write_int(54, fd);
	write_int(40, fd);
	write_int(m->p.r[0], fd);
	write_int(m->p.r[1], fd);
	write_int(2097153, fd);
	write_int(0, fd);
	write_int(m->render.size_line * m->render.h, fd);
	write_int(2835, fd);
	write_int(2835, fd);
	write_int(0, fd);
	write_int(0, fd);
	i = m->render.h;
	while (--i >= 0)
		write(fd, m->render.img + (i * m->render.size_line),
			m->render.size_line);
}
