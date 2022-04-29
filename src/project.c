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
 * Rotate point around the y axis by yaw radians
 */
static void	rot_yaw(t_point *point, double yaw)
{
	double	cosine;
	double	sine;
	int		x;
	int		z;

	cosine = cos(yaw);
	sine = sin(yaw);
	x = point->x;
	z = point->z;
	point->x = (int)round(x * cosine + z * sine);
	point->z = (int)round(z * cosine - x * sine);
}

/**
 * Rotate point around the x axis by pitch radians
 */
static void	rot_pitch(t_point *point, double pitch)
{
	double	cosine;
	double	sine;
	int		y;
	int		z;

	cosine = cos(pitch);
	sine = sin(pitch);
	y = point->y;
	z = point->z;
	point->y = (int)round(y * cosine - z * sine);
	point->z = (int)round(z * cosine + y * sine);
}

/**
 * Rotate point around the z axis by roll radians 
 */
static void	rot_roll(t_point *point, double roll)
{
	double	cosine;
	double	sine;
	int		x;
	int		y;

	x = point->x;
	y = point->y;
	cosine = cos(roll);
	sine = sin(roll);
	point->x = (int)round(x * cosine - y * sine);
	point->y = (int)round(y * cosine + x * sine);
}

/**
 * Rotate point according to the cam settings, then rotate some more for
 * a perfect isometric view
 */
static void	rotate(t_point *point, t_cam *cam)
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
	subtract(&point, &cam->focal);
	point.x *= cam->scale;
	point.y *= cam->scale;
	point.z *= (int)(cam->scale * cam->z_scale);
	rotate(&point, cam);
	point.x += cam->offset.x;
	point.y += cam->offset.y;
	return (point);
}
