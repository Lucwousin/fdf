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

static bool	should_handle_event(mlx_key_data_t event)
{
	return (event.key != MLX_CONTROL
		&& (event.action == MLX_PRESS || event.action == MLX_REPEAT));
}

static bool	is_ctrl_down(mlx_key_data_t event)
{
	return ((event.modifier & MLX_CONTROL) != 0);
}

void	key_event(mlx_key_data_t e, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (!should_handle_event(e))
		return ;
	if (e.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	else if (e.key == MLX_KEY_A || e.key == MLX_KEY_D || e.key == MLX_KEY_W
		|| e.key == MLX_KEY_S || e.key == MLX_KEY_Q || e.key == MLX_KEY_E)
		rotate_cam(&fdf->cam, e.key, is_ctrl_down(e));
	else if (e.key == MLX_KEY_LEFT || e.key == MLX_KEY_RIGHT
		|| e.key == MLX_KEY_UP || e.key == MLX_KEY_DOWN)
		translate_cam(&fdf->cam, e.key, is_ctrl_down(e));
	else if (e.key == MLX_KEY_PAGE_UP || e.key == MLX_KEY_PAGE_DOWN)
		zscale_cam(&fdf->cam, e.key == MLX_KEY_PAGE_DOWN, is_ctrl_down(e));
	else if (e.key == MLX_KEY_0)
		reset_cam(fdf);
	else if (e.key == MLX_KEY_C)
		fdf->col = (fdf->col + 1) % END;
	else
		return ;
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
