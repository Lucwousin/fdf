/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 11:55:53 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/22 11:55:53 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>

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

void	draw_between(t_fdf *data, t_point a, t_point b)
{
	mlx_image_t	*img;
	
	img = data->img;
	a = project(a, &data->cam);
	b = project(b, &data->cam);
	if (a.x < 0 && b.x < 0)
		return ;
	if ((uint32_t)a.x >= img->width && (uint32_t)b.x >= img->width)
		return ;
	if (a.y < 0 && b.y < 0)
		return ;
	if ((uint32_t)a.y >= img->height && (uint32_t)b.y >= img->height)
		return ;
	draw_line(img, a, b);
}

void	render(t_fdf *data)
{
	mlx_image_t	*img;

	img = data->img;
	ft_bzero(img->pixels, img->width * img->height * sizeof(uint32_t));
	for (uint32_t x = 0; x <= data->map.max_x; x++) {
		for (uint32_t y = 0; y <= data->map.max_y; y++) {
			t_point *p = data->map.points[y][x];
			if (x < data->map.max_x)
				draw_between(data, *p, *data->map.points[y][x + 1]);
			if (y < data->map.max_y)
				draw_between(data, *p, *data->map.points[y + 1][x]);
		}
	}
	draw_test(img, &data->cam);
}