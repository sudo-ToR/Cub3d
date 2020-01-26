#include "cub3d.h"

void draw_rectangle(t_vector2 pos, t_vector2 size, t_color color)
{
	int x;
	int y;

	x = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			put_pixel(create_vector2(x + pos.x, y + pos.y), color);
			y++;
		}
		x++;
	}
}
