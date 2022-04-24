/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucas <lucas@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 17:11:19 by lucas         #+#    #+#                 */
/*   Updated: 2022/04/21 17:11:19 by lucas         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <stdio.h>

void	key_event(mlx_key_data_t event, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (event.action == MLX_PRESS || event.action == MLX_REPEAT)
	{
		if (event.key == MLX_KEY_ESCAPE)
			mlx_close_window(fdf->mlx);
		else if (event.key == MLX_KEY_A)
			fdf->cam.yaw -= 0.05;
		else if (event.key == MLX_KEY_D)
			fdf->cam.yaw += 0.05;
		else if (event.key == MLX_KEY_W)
			fdf->cam.pitch += 0.05;
		else if (event.key == MLX_KEY_S)
			fdf->cam.pitch -= 0.05;
		else if (event.key == MLX_KEY_Q)
			fdf->cam.roll -= 0.05;
		else if (event.key == MLX_KEY_E)
			fdf->cam.roll += 0.05;
		else if (event.key == MLX_KEY_0)
			reset_cam(fdf);
		render(fdf);
	}
}

void	scroll_event(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	(void) xdelta;
	fdf = param;
	if (ydelta > 0)
		fdf->cam.scale += 1;
	else if (ydelta < 0)
		fdf->cam.scale -= 1;
	else
		return ;
	render(fdf);
}

void	resize_event(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	mlx_resize_image(fdf->img, width, height);
	render(fdf);
}
