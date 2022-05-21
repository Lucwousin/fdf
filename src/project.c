/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   project.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 12:26:18 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/29 12:26:18 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

/**
 * Rotate point according to the cam settings, then rotate some more for
 * a perfect isometric view
 */
static void	rotate(t_ivec *point, t_dmat mat)
{
	t_dvec	vec;

	vec = ivec_to_dvec(*point);
	vec = mult_vec(mat, vec);
	*point = dvec_to_ivec(vec);
	//rot_yaw(point, -M_PI_4);
	//rot_pitch(point, atan(M_SQRT1_2));
	//rot_roll(point, M_PI / 3);
}

/**
 * Project point onto the screen, according to the cam settings 
 */
t_point	project(t_point point, t_cam *cam)
{
	point.vec -= cam->focal;
	point.vec *= cam->scale;
	point.vec[Z] = (int32_t)(point.vec[Z] * cam->z_scale);
	rotate(&point.vec, cam->matrix);
	point.vec += cam->offset;
	return (point);
}
