/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 13:55:02 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/22 13:55:02 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static bool	in_bounds(mlx_image_t *img, t_line *line)
{
	int32_t	x;
	int32_t	y;

	x = line->x;
	y = line->y;
	if (x >= 0 && y >= 0)
		if (x < (int32_t) img->width && y < (int32_t) img->height)
			return (true);
	return (false);
}

static t_line	get_line_info(t_fdf *data, t_point a, t_point b)
{
	t_line	line;

	line.dx = abs(b.vec[X] - a.vec[X]);
	line.dy = abs(b.vec[Y] - a.vec[Y]);
	if (a.vec[X] < b.vec[X])
		line.x_step = 1;
	else
		line.x_step = -1;
	if (a.vec[Y] < b.vec[Y])
		line.y_step = 1;
	else
		line.y_step = -1;
	line.x = a.vec[X];
	line.y = a.vec[Y];
	init_line_colours(data, line.colours, a, b);
	return (line);
}

void	draw_line(mlx_image_t *img, t_point a, t_point b, t_fdf *data)
{
	t_line	line;
	int32_t	error;

	line = get_line_info(data, a, b);
	error = (int32_t) line.dx - (int32_t) line.dy;
	while (true)
	{
		if (in_bounds(img, &line))
			mlx_put_pixel(img, line.x, line.y, inter_line_colour(a, b, &line));
		if (line.x == b.vec[X] && line.y == b.vec[Y])
			return ;
		if (error >= 0)
		{
			line.x += line.x_step;
			error -= (int32_t) line.dy;
		}
		if (error < 0)
		{
			line.y += line.y_step;
			error += (int32_t) line.dx;
		}
	}
}
