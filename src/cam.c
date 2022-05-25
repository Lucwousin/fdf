/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cam.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:10:31 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/19 16:10:31 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

const static t_axis_info	g_axis_info[] = {
[MLX_KEY_W] = {X, true},
[MLX_KEY_S] = {X, false},
[MLX_KEY_A] = {Y, false},
[MLX_KEY_D] = {Y, true},
[MLX_KEY_Q] = {Z, false},
[MLX_KEY_E] = {Z, true},
[MLX_KEY_RIGHT] = {X, false},
[MLX_KEY_LEFT] = {X, true},
[MLX_KEY_DOWN] = {Y, false},
[MLX_KEY_UP] = {Y, true}
};

void	reset_cam(t_fdf *data)
{
	t_cam	*cam;

	cam = &data->cam;
	cam->scale = 50;
	cam->z_scale = 1.0;
	cam->angles = (t_dvec){0, 0, 0, 0};
	cam->old_angles = (t_dvec){0, 0, 0, 0};
	cam->rot_q = init_isometric_quaternion();
	cam->focal[X] = (int32_t) data->map.max_x / 2;
	cam->focal[Y] = (int32_t) data->map.max_y / 2;
	cam->focal[Z] = (data->map.max_z - data->map.min_z) / 2 + data->map.min_z;
	cam->offset[X] = (int32_t)(data->img->width / 2);
	cam->offset[Y] = (int32_t)(data->img->height / 2);
	cam->offset[Z] = 0;
	identity_matrix(cam->matrix);
}

void	rotate_cam(t_cam *cam, keys_t key, bool modifier)
{
	double	amount;
	t_axis	axis;
	bool	decrement;

	axis = g_axis_info[key].axis;
	decrement = g_axis_info[key].decrement;
	amount = M_PI / 60;
	if (modifier)
		amount *= 10;
	if (decrement)
		amount *= -1;
	cam->angles[axis] += amount;
	if (cam->angles[axis] > 2 * M_PI)
		cam->angles[axis] -= 2 * M_PI;
	else if (cam->angles[axis] < 0)
		cam->angles[axis] += 2 * M_PI;
}

void	translate_cam(t_cam *cam, keys_t key, bool modifier)
{
	int32_t	amount;
	t_axis	axis;
	bool	decrement;

	axis = g_axis_info[key].axis;
	decrement = g_axis_info[key].decrement;
	amount = 1;
	if (modifier)
		amount *= 10;
	if (decrement)
		amount *= -1;
	cam->offset[axis] += amount;
}

void	zscale_cam(t_cam *cam, bool dec, bool modifier)
{
	double	amount;

	amount = 0.05;
	if (modifier)
		amount *= 10;
	if (dec)
		amount *= -1;
	cam->z_scale += amount;
}
