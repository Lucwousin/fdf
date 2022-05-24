/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 17:51:49 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/19 17:51:49 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static t_dvec	mul_quaternion(t_dvec a, t_dvec b)
{
	return ((t_dvec){
		a[W] * b[X] + a[X] * b[W] + a[Y] * b[Z] - a[Z] * b[Y],
		a[W] * b[Y] - a[X] * b[Z] + a[Y] * b[W] + a[Z] * b[X],
		a[W] * b[Z] + a[X] * b[Y] - a[Y] * b[X] + a[Z] * b[W],
		a[W] * b[W] - a[X] * b[X] - a[Y] * b[Y] - a[Z] * b[Z]
	});
}

static void	quaternion_to_matrix(t_dmat mat, t_dvec q)
{
	mat[0] = (t_dvec){
		1 - 2 * (q[Y] * q[Y] + q[Z] * q[Z]),
		2 * (q[X] * q[Y] - q[W] * q[Z]),
		2 * (q[X] * q[Z] + q[W] * q[Y]),
	};
	mat[1] = (t_dvec){
		2 * (q[X] * q[Y] + q[W] * q[Z]),
		1 - 2 * (q[X] * q[X] + q[Z] * q[Z]),
		2 * (q[Y] * q[Z] - q[W] * q[X])
	};
	mat[2] = (t_dvec){
		2 * (q[X] * q[Z] - q[W] * q[Y]),
		2 * (q[Y] * q[Z] + q[W] * q[X]),
		1 - 2 * (q[X] * q[X] + q[Y] * q[Y]),
	};
	mat[3] = (t_dvec){0, 0, 0, 1};
}

static t_dvec	new_quaternion(t_dvec unit, double delta_rot)
{
	unit *= sin(delta_rot / 2);
	unit[W] = cos(delta_rot / 2);
	return (unit);
}

t_dvec	init_isometric_quaternion(void)
{
	t_dvec	roll;
	t_dvec	pitch;

	roll = new_quaternion((t_dvec){0, 0, 1, 0}, M_PI_4);
	pitch = new_quaternion((t_dvec){1, 0, 0, 0}, atan(M_SQRT2));
	return (mul_quaternion(pitch, roll));
}

void	update_rotation(t_cam *cam)
{
	const t_dvec	uvs[3] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0}
	};
	t_dvec			tmp_quaternion;
	t_dvec			delta_angles;
	t_angle			a;

	delta_angles = cam->old_angles - cam->angles;
	a = PITCH;
	while (a <= ROLL)
	{
		if (delta_angles[a] != 0)
		{
			tmp_quaternion = new_quaternion(uvs[a], delta_angles[a]);
			cam->rot_q = mul_quaternion(tmp_quaternion, cam->rot_q);
		}
		++a;
	}
	quaternion_to_matrix(cam->matrix, cam->rot_q);
	cam->old_angles = cam->angles;
}
