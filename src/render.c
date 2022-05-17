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

static void	draw_between(t_fdf *data, t_point a, t_point b)
{
	mlx_image_t	*img;

	img = data->img;
	a = project(a, &data->cam);
	b = project(b, &data->cam);
	if (a.x < 0 && b.x < 0)
		return ;
	if (a.x >= (int32_t)img->width && b.x >= (int32_t)img->width)
		return ;
	if (a.y < 0 && b.y < 0)
		return ;
	if (a.y >= (int32_t)img->height && b.y >= (int32_t)img->height)
		return ;
	draw_line(img, a, b);
}

void	render(t_fdf *data)
{
	mlx_image_t	*img;
	t_point		point;
	uint32_t	x;
	uint32_t	y;

	img = data->img;
	ft_bzero(img->pixels, img->width * img->height * sizeof(uint32_t));
	x = 0;
	while (x <= data->map.max_x)
	{
		y = 0;
		while (y <= data->map.max_y)
		{
			point = *data->map.points[y][x];
			if (x < data->map.max_x)
				draw_between(data, point, *data->map.points[y][x + 1]);
			if (y < data->map.max_y)
				draw_between(data, point, *data->map.points[y + 1][x]);
			++y;
		}
		++x;
	}
}
