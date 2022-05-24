/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 17:11:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/21 17:11:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"

void	key_event(mlx_key_data_t event, void *param)
{
	t_fdf	*fdf;
	bool	modifier;

	fdf = param;
	modifier = (event.modifier & MLX_CONTROL) != 0;
	if (event.action != MLX_PRESS && event.action != MLX_REPEAT)
		return ;
	if (event.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	else if (event.key == MLX_KEY_A || event.key == MLX_KEY_D)
		rotate_cam(&fdf->cam, YAW, event.key == MLX_KEY_D, modifier);
	else if (event.key == MLX_KEY_W || event.key == MLX_KEY_S)
		rotate_cam(&fdf->cam, PITCH, event.key == MLX_KEY_W, modifier);
	else if (event.key == MLX_KEY_Q || event.key == MLX_KEY_E)
		rotate_cam(&fdf->cam, ROLL, event.key == MLX_KEY_E, modifier);
	else if (event.key == MLX_KEY_PAGE_UP || event.key == MLX_KEY_PAGE_DOWN)
		zscale_cam(&fdf->cam, event.key == MLX_KEY_PAGE_DOWN, modifier);
	else if (event.key == MLX_KEY_LEFT || event.key == MLX_KEY_RIGHT)
		translate_cam(&fdf->cam, X, event.key == MLX_KEY_LEFT, modifier);
	else if (event.key == MLX_KEY_UP || event.key == MLX_KEY_DOWN)
		translate_cam(&fdf->cam, Y, event.key == MLX_KEY_UP, modifier);
	else if (event.key == MLX_KEY_0)
		reset_cam(fdf);
	else if (event.key == MLX_KEY_C)
		fdf->col = (fdf->col + 1) % END;
	render(fdf);
}

void	scroll_event(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;
	int32_t	zoom_amt;

	(void) xdelta;
	fdf = param;
	if (ydelta > 0)
		zoom_amt = 1;
	else if (ydelta < 0)
		zoom_amt = -1;
	else
		return ;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_CONTROL)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT_CONTROL))
		zoom_amt *= 10;
	fdf->cam.scale += zoom_amt;
	render(fdf);
}

void	resize_event(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	fdf->cam.offset[X] += (width - (int32_t) fdf->img->width) / 2;
	fdf->cam.offset[Y] += (height - (int32_t) fdf->img->height) / 2;
	mlx_resize_image(fdf->img, width, height);
	render(fdf);
}
