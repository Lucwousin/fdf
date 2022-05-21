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
#define CAM_DOUBLE_AMT	0.05

void	reset_cam(t_fdf *data)
{
	t_cam	*cam;

	cam = &data->cam;
	cam->scale = 50;
	cam->z_scale = 1.0;
	cam->angles = (t_dvec){0, 0, 0, 0};
	cam->old_angles = (t_dvec){0, 0, 0, 0};
	cam->rot_q = (t_dvec){0, 0, 0, 1};
	cam->focal[X] = (int32_t) data->map.max_x / 2;
	cam->focal[Y] = (int32_t) data->map.max_y / 2;
	cam->focal[Z] = (data->map.max_z - data->map.min_z) / 2 + data->map.min_z;
	cam->offset[X] = (int32_t)(data->img->width / 2);
	cam->offset[Y] = (int32_t)(data->img->height / 2);
	cam->offset[Z] = 0;
	reset_matrix(cam->matrix);
}

void	rotate_cam(t_cam *cam, t_angle angle, bool dec, bool modifier)
{
	double	amount;

	amount = CAM_DOUBLE_AMT;
	if (modifier)
		amount *= 10;
	if (dec)
		amount *= -1;
	cam->angles[angle] += amount;
	if (cam->angles[angle] > 2 * M_PI)
		cam->angles[angle] -= 2 * M_PI;
	else if (cam->angles[angle] < 0)
		cam->angles[angle] += 2 * M_PI;
}

void	translate_cam(t_cam *cam, t_axis axis, bool dec, bool modifier)
{
	int32_t	amount;

	amount = 1;
	if (modifier)
		amount *= 10;
	if (dec)
		amount *= -1;
	cam->offset[axis] += amount;
}

void	zscale_cam(t_cam *cam, bool dec, bool modifier)
{
	double	amount;

	amount = CAM_DOUBLE_AMT;
	if (modifier)
		amount *= 10;
	if (dec)
		amount *= -1;
	cam->z_scale += amount;
}
