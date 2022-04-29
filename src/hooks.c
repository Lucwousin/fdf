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
#define CAM_DOUBLE_AMT	0.05

static void	change_cam_d(double *setting, bool decrement)
{
	if (decrement)
		*setting -= CAM_DOUBLE_AMT;
	else
		*setting += CAM_DOUBLE_AMT;
}

static void	change_cam_i(int *setting, bool decrement, bool modifier)
{
	int32_t	amount;

	amount = 1;
	if (modifier)
		amount *= 10;
	if (decrement)
		amount *= -1;
	*setting += amount;
}

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
		change_cam_d(&fdf->cam.yaw, event.key == MLX_KEY_A);
	else if (event.key == MLX_KEY_W || event.key == MLX_KEY_S)
		change_cam_d(&fdf->cam.pitch, event.key == MLX_KEY_S);
	else if (event.key == MLX_KEY_Q || event.key == MLX_KEY_E)
		change_cam_d(&fdf->cam.roll, event.key == MLX_KEY_Q);
	else if (event.key == MLX_KEY_PAGE_UP || event.key == MLX_KEY_PAGE_DOWN)
		change_cam_d(&fdf->cam.z_scale, event.key == MLX_KEY_PAGE_DOWN);
	else if (event.key == MLX_KEY_LEFT || event.key == MLX_KEY_RIGHT)
		change_cam_i(&fdf->cam.offset.x, event.key == MLX_KEY_LEFT, modifier);
	else if (event.key == MLX_KEY_UP || event.key == MLX_KEY_DOWN)
		change_cam_i(&fdf->cam.offset.y, event.key == MLX_KEY_UP, modifier);
	else if (event.key == MLX_KEY_0)
		reset_cam(fdf);
	render(fdf);
}

void	scroll_event(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;
	int		zoom_amt;

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
	mlx_resize_image(fdf->img, width, height);
	render(fdf);
}
