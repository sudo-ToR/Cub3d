/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:24:49 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/07 18:29:06 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_image
{
    void            *img_ptr;
    unsigned int    *data;
    int             width;
    int             heigth;
    int             bpp;
    int             size_line;
    int             endian;

}               t_image;

typedef  struct s_mlx
{
        void *mlx_ptr;
        void *win_ptr;
}               t_mlx;

typedef  struct s_player
{
    int x;
    int y;
}               t_player;

typedef     struct s_all
{
    t_player player;
    t_mlx mlx;
    t_image renderer;
}                   t_all;

typedef unsigned int t_uint;

t_uint  ft_color(int a, int r, int g, int b)
{
    return (a * 256 * 256 * 256 + r * 256 * 256 + g * 256 + b);
}


char     **ft_init(char **map, t_all *a)
{
    int i = -1;
    int y = 0;


    map = malloc(sizeof(char *) * 10);
    while (++i < 10)
        map[i] = malloc(sizeof(char) * 11);
    i = -1;
    while (++i < 10)
    {
        map[0][i] = '1';
        map[9][i] = '1';
        y = -1;
        map[i][10] = 0;
    }
    i = 0;
    while (++i < 9)
    {
        y = -1;
        while (++y < 10)
            map[i][y] = (y == 0 || y == 9) ? '1' : '0';
    }
       return(map);
}

int     main()
{
    char **map;
    t_all a;
    int i = 0;
    int y;

    map = ft_init(map, &a);
    
    while (map[i++])
    {
        y = 0;
        while (map[i][y])
        {
            if ()
        }
    }
    
}