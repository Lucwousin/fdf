/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 14:41:43 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/23 14:41:43 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	init_mlx_hooks(t_fdf *data)
{
	mlx_key_hook(data->mlx, key_event, data);
	mlx_scroll_hook(data->mlx, scroll_event, data);
	mlx_resize_hook(data->mlx, resize_event, data);
}

void	init_mlx(t_fdf *data, const char *map)
{
	data->title = ft_strjoin("FdF - ", map);
	if (!data->title)
		error(data, ERR_MAL_TITLE, true);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, data->title, true);
	if (!data->mlx)
		error(data, ERR_MLX_INIT, false);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		error(data, ERR_MLX_IMG, false);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	init_mlx_hooks(data);
}

static bool	init_map_data(t_map *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	map->min_z = INT32_MAX;
	map->max_z = INT32_MIN;
	while (map->points[y])
	{
		x = 0;
		while (map->points[y][x])
		{
			map->points[y][x]->vec[X] = (int32_t) x;
			map->points[y][x]->vec[Y] = (int32_t) y;
			map->min_z = ft_min(map->points[y][x]->vec[Z], map->min_z);
			map->max_z = ft_max(map->points[y][x]->vec[Z], map->max_z);
			++x;
		}
		if (map->max_x == 0)
			map->max_x = x - 1;
		else if (map->max_x != x - 1)
			return (false);
		++y;
	}
	map->max_y = y - 1;
	return (true);
}

void	init_map(t_fdf *data, const char *map)
{
	if (!parse(&data->map, map))
		error(data, ERR_MAP_PARSE, true);
	if (!init_map_data(&data->map))
		error(data, ERR_MAP_VALID, false);
}
