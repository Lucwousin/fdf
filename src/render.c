/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucas <lucas@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 11:55:53 by lucas         #+#    #+#                 */
/*   Updated: 2022/04/22 11:55:53 by lucas         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>

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

static void	rotate(t_point *point, t_cam *cam)
{
	double	yaw;
	double	pitch;
	double	roll;

	yaw = cam->yaw;
	pitch = cam->pitch;
	roll = cam->roll;
	rot_yaw(point, yaw);
	rot_pitch(point, pitch);
	rot_roll(point, roll);
	rot_yaw(point, -M_PI_4);
	rot_pitch(point, atan(M_SQRT1_2));
	rot_roll(point, M_PI / 3);
}

t_point	project(t_point point, t_cam *cam)
{
	subtract(&point, &cam->focal);
	point.x *= cam->scale;
	point.y *= cam->scale;
	point.z *= cam->scale;
	rotate(&point, cam);
	point.x += cam->offset.x;
	point.y += cam->offset.y;
	return (point);
}

void	draw_test(mlx_image_t *img, t_cam *cam)
{
	t_point origin = (t_point){0, 0, 0, get_rgba(0xFFFFFFFF)};
	t_point x_axis = {1, 0, 0, get_rgba(0xFF0000FF)};
	t_point y_axis = {0, 1, 0, get_rgba(0x00FF00FF)};
	t_point z_axis = {0, 0, 1, get_rgba(0x0000FFFF)};
	origin = project(origin, cam);
	x_axis = project(x_axis, cam);
	y_axis = project(y_axis, cam);
	z_axis = project(z_axis, cam);
	draw_line(img, origin, x_axis);
	draw_line(img, origin, y_axis);
	draw_line(img, origin, z_axis);
}

void	render(t_fdf *data)
{
	mlx_image_t	*img;

	img = data->img;
	ft_bzero(img->pixels, img->width * img->height * sizeof(uint32_t));
	int x = 0;
	for (;x <= data->map.max_x; x++) {
		for (int y = 0; y <= data->map.max_y; y++) {
			t_point *a = data->map.points[y][x];
			if (x < data->map.max_x)
				draw_line(img, project(*a, &data->cam), project(*data->map.points[y][x + 1], &data->cam));
			if (y < data->map.max_y)
				draw_line(img, project(*a, &data->cam), project(*data->map.points[y + 1][x], &data->cam));
		}
	}
	draw_test(img, &data->cam);
}