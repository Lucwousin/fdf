/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 16:47:43 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/20 16:47:43 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

static void	cleanup(t_fdf *data)
{
	if (data->title)
		free(data->title);
	if (data->map.points)
		cleanup_map(&data->map);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx)
		mlx_terminate(data->mlx);
}

static void	error(t_fdf *data, const char *reason)
{
	ft_printf("%s\n", reason);
	cleanup(data);
	exit(EXIT_FAILURE);
}

static void	init_mlx_hooks(t_fdf *data)
{
	mlx_key_hook(data->mlx, key_event, data);
	mlx_scroll_hook(data->mlx, scroll_event, data);
	mlx_resize_hook(data->mlx, resize_event, data);
}

void	reset_cam(t_fdf *data)
{
	t_cam	*cam;

	cam = &data->cam;
	cam->scale = 50;
	cam->z_scale = 1.0;
	cam->pitch = 0;
	cam->yaw = 0;
	cam->roll = 0;
	cam->focal[X] = (int32_t) data->map.max_x / 2;
	cam->focal[Y] = (int32_t) data->map.max_y / 2;
	cam->focal[Z] = (data->map.max_z - data->map.min_z) / 2 + data->map.min_z;
	cam->offset[X] = (int32_t)(data->img->width / 2);
	cam->offset[Y] = (int32_t)(data->img->height / 2);
	cam->offset[Z] = 0;
}

int	main(int argc, char **argv)
{
	t_fdf	data;

	ft_bzero(&data, sizeof(t_fdf));
	if (argc < 2)
		error(&data, "Error: Not enough arguments\nUsage: ./fdf <map_file>");
	data.title = ft_strjoin("FdF - ", argv[1]);
	if (!data.title)
		error(&data, "Error: Failed to allocate title (lol)");
	if (!parse(&data.map, argv[1]))
		error(&data, "Error: Invalid map");
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, data.title, true);
	if (!data.mlx)
		error(&data, "Error: MLX failed to initialize");
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data.img)
		error(&data, "Error: Could not create image");
	reset_cam(&data);
	render(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_mlx_hooks(&data);
	mlx_loop(data.mlx);
	cleanup(&data);
}
