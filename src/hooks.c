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
#define	CAM_SETTING_AMOUNT	0.05

static void	change_cam_setting(double *setting, bool decrement)
{
	if (decrement)
		*setting -= CAM_SETTING_AMOUNT;
	else
		*setting += CAM_SETTING_AMOUNT;
}

void	key_event(mlx_key_data_t event, void *param)
{
	t_fdf	*fdf;
	keys_t	key;

	fdf = param;
	key = event.key;
	if (event.action == MLX_PRESS || event.action == MLX_REPEAT)
	{
		if (key == MLX_KEY_ESCAPE)
			mlx_close_window(fdf->mlx);
		else if (key == MLX_KEY_A || key == MLX_KEY_D)
			change_cam_setting(&fdf->cam.yaw, key == MLX_KEY_A);
		else if (key == MLX_KEY_W || key == MLX_KEY_S)
			change_cam_setting(&fdf->cam.pitch, key == MLX_KEY_S);
		else if (key == MLX_KEY_Q || key == MLX_KEY_E)
			change_cam_setting(&fdf->cam.roll, key == MLX_KEY_Q);
		else if (key == MLX_KEY_PAGE_UP || key == MLX_KEY_PAGE_DOWN)
			change_cam_setting(&fdf->cam.z_scale, key == MLX_KEY_PAGE_DOWN);
		else if (key == MLX_KEY_0)
			reset_cam(fdf);
		render(fdf);
	}
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
