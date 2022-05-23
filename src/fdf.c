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
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void	error(t_fdf *data, char *reason, bool in_lib)
{
	if (in_lib)
		perror(reason);
	else
		ft_putendl_fd(reason, STDERR_FILENO);
	cleanup(data);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_fdf	data;

	ft_bzero(&data, sizeof(t_fdf));
	if (argc < 2)
		error(&data, ERR_ARGS, false);
	init_map(&data, argv[1]);
	init_mlx(&data, argv[1]);
	reset_cam(&data);
	render(&data);
	mlx_loop(data.mlx);
	cleanup(&data);
}
