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

t_dvec	mult_quaternion(t_dvec a, t_dvec b)
{
	return ((t_dvec){
		a[W] * b[X] + a[X] * b[W] + a[Y] * b[Z] - a[Z] * b[Y],
		a[W] * b[Y] - a[X] * b[Z] + a[Y] * b[W] + a[Z] * b[X],
		a[W] * b[Z] + a[X] * b[Y] - a[Y] * b[X] + a[Z] * b[W],
		a[W] * b[W] - a[X] * b[X] - a[Y] * b[Y] - a[Z] * b[Z]
	});
}

void	create_q_matrix(t_dmat mat, t_dvec q)
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
}

t_dvec	new_quat(t_dmat mat, t_dvec unit, double delta_rot)
{
	(void) mat;
	// Rotate unit vector according to previous rotation
	//mult_vec(mat, unit);
	unit *= sin(delta_rot / 2);
	unit[W] = cos(delta_rot / 2);
	return (unit);
}

void	update_rotation(t_cam *cam)
{
	const t_dvec	uvs[3] = {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0}
	};
	t_dvec	quat;
	t_dvec	delta_angles;
	t_angle	a;

	delta_angles = cam->old_angles - cam->angles;
	a = PITCH;
	while (a <= ROLL)
	{
		if (delta_angles[a] != 0)
		{
			quat = new_quat(cam->matrix, uvs[a], delta_angles[a]);
			cam->rot_q = mult_quaternion(quat, cam->rot_q);
		}
		++a;
	}
	create_q_matrix(cam->matrix, cam->rot_q);
	cam->old_angles = cam->angles;
}
