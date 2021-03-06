/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:23:42 by lnoirot           #+#    #+#             */
/*   Updated: 2021/01/03 20:49:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char		*check_argument(char *name_file)
{
	int length;
	int	fd;

	fd = open(name_file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return ("Error\nunexistant file\n");
	}
	if ((length = ft_strlen(name_file)) < 4)
		return ("Error\nFirst argument must be a .cub file\n");
	if (ft_strncmp(name_file + (length - 4), ".cub", 4))
		return ("Error\nFirst argument must be a .cub file\n");
	return (NULL);
}

int			main(int ac, char **av)
{
	int		fd;
	t_mlx	m;
	char	*str;

	ft_memset(&m, 0, sizeof(m));
	if (ac == 1)
		return (ft_printf("Error\nMissing argument\n"));
	if ((str = check_argument(av[1])))
		return (ft_printf("%s", str));
	if (ft_pars(fd = open(av[1], O_RDONLY), &m.p, &m))
		return (1);
	if (ft_init_mlx(&m))
	{
		ft_printf("Error\nWrong format of textures\n");
		exit_game(&m, 1);
	}
	if (ac >= 3 && !ft_strcmp(av[2], "--save"))
	{
		draw_image(m.cam_angle, &m);
		make_screenshot(&m);
		exit_game(&m, 1);
		return (ft_printf("save option\n"));
	}
	loop_win(&m);
	return (0);
}
