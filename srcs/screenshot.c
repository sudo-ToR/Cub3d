/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:41:45 by user42            #+#    #+#             */
/*   Updated: 2020/11/15 18:57:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_screenshot(t_mlx *m)
{
	int		fd;
	int		i;
	int		size;


	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	size = m->p.r[0] * m->p.r[1] * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size, sizeof(size));
	size = 0;
	write(fd, &size, sizeof(size));
	size = 54;
	write(fd, &size, sizeof(size));
	size = 40;
	write(fd, &size, sizeof(size));
	write(fd, &m->p.r[0], sizeof(m->p.r[0]));
	write(fd, &m->p.r[1], sizeof(m->p.r[1]));
	size = 2097153;
	write(fd, &size, sizeof(size));
	size = 0;
	write(fd, &size, sizeof(size));
	size = m->render.size_line * m->render.h;
	write(fd, &size, sizeof(m->render.size_line));
	size = 2835;
	write(fd, &size, sizeof(size));
	write(fd, &size, sizeof(size));
	size = 0;
	write(fd, &size, sizeof(size));
	write(fd, &size, sizeof(size));
	i = m->render.h;
	while(--i >= 0)
		write(fd, m->render.img + (i * m->render.size_line), m->render.size_line);
}