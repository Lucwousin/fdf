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

static t_point	project(t_point point, t_cam *cam)
{
	t_dvec	vec;

	point.vec -= cam->focal;
	point.vec *= cam->scale;
	point.vec[Z] = (int32_t)(point.vec[Z] * cam->z_scale);
	vec = ivec_to_dvec(point.vec);
	vec = mult_vec(cam->matrix, vec);
	point.vec = dvec_to_ivec(vec);
	point.vec += cam->offset;
	return (point);
}

static bool	on_screen(t_ivec a, t_ivec b, uint32_t w, uint32_t h)
{
	if (a[X] < 0 && b[X] < 0)
		return (false);
	if (a[X] >= (int32_t) w && b[X] >= (int32_t) w)
		return (false);
	if (a[Y] < 0 && b[Y] < 0)
		return (false);
	if (a[Y] >= (int32_t) h && b[Y] >= (int32_t) h)
		return (false);
	return (true);
}

static void	draw_between(t_fdf *data, t_point a, t_point b)
{
	mlx_image_t	*img;

	img = data->img;
	a = project(a, &data->cam);
	b = project(b, &data->cam);
	if (!on_screen(a.vec, b.vec, img->width, img->height))
		return ;
	draw_line(img, a, b);
}

static void	clear_image(mlx_image_t *img)
{
	ft_bzero(img->pixels, img->width * img->height * sizeof(uint32_t));
}

void	render(t_fdf *data)
{
	t_point		point;
	uint32_t	x;
	uint32_t	y;

	clear_image(data->img);
	update_rotation(&data->cam);
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
