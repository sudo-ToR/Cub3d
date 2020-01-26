#include "cub3d.h"

t_vector2 create_vector2(int x, int y)
{
	t_vector2 result;

	result.x = x;
	result.y = y;
	return (result);
}

t_vector2 *malloc_vector2(int x, int y)
{
	t_vector2 *result;

	result = (t_vector2 *)malloc(sizeof(t_vector2));
	if (result == NULL)
		return (NULL);

	*result = create_vector2(x, y);

	return (result);
}

void destroy_vector2(t_vector2 to_delete)
{
	(void)to_delete;
}

void free_vector2(t_vector2 *to_free)
{
	destroy_vector2(*to_free);
	free(to_free);
}
