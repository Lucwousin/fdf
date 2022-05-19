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
#include <math.h>

/**
 * Rotate vec around the y axis by yaw radians
 */
static void	rot_yaw(t_ivec *vec, double yaw)
{
	double	cosine;
	double	sine;
	int32_t	x;
	int32_t	z;

	cosine = cos(yaw);
	sine = sin(yaw);
	x = (*vec)[X];
	z = (*vec)[Z];
	(*vec)[X] = (int32_t)round(x * cosine + z * sine);
	(*vec)[Z] = (int32_t)round(z * cosine - x * sine);
}

/**
 * Rotate vec around the x axis by pitch radians
 */
static void	rot_pitch(t_ivec *vec, double pitch)
{
	double	cosine;
	double	sine;
	int32_t	y;
	int32_t	z;

	cosine = cos(pitch);
	sine = sin(pitch);
	y = (*vec)[Y];
	z = (*vec)[Z];
	(*vec)[Y] = (int32_t)round(y * cosine - z * sine);
	(*vec)[Z] = (int32_t)round(z * cosine + y * sine);
}

/**
 * Rotate vec around the z axis by roll radians 
 */
static void	rot_roll(t_ivec *vec, double roll)
{
	double	cosine;
	double	sine;
	int32_t	x;
	int32_t	y;

	x = (*vec)[X];
	y = (*vec)[Y];
	cosine = cos(roll);
	sine = sin(roll);
	(*vec)[X] = (int32_t)round(x * cosine - y * sine);
	(*vec)[Y] = (int32_t)round(y * cosine + x * sine);
}

/**
 * Rotate point according to the cam settings, then rotate some more for
 * a perfect isometric view
 */
static void	rotate(t_ivec *point, t_cam *cam)
{
	rot_yaw(point, cam->yaw);
	rot_pitch(point, cam->pitch);
	rot_roll(point, cam->roll);
	rot_yaw(point, -M_PI_4);
	rot_pitch(point, atan(M_SQRT1_2));
	rot_roll(point, M_PI / 3);
}

/**
 * Project point onto the screen, according to the cam settings 
 */
t_point	project(t_point point, t_cam *cam)
{
	point.vec -= cam->focal;
	point.vec *= cam->scale;
	point.vec[Z] = (int32_t)(point.vec[Z] * cam->z_scale);
	rotate(&point.vec, cam);
	point.vec += cam->offset;
	return (point);
}
