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

static t_line	get_line_info(t_point a, t_point b)
{
	t_line	line;

	line.delta[X] = abs(b.vec[X] - a.vec[X]);
	line.delta[Y] = abs(b.vec[Y] - a.vec[Y]);
	if (a.vec[X] < b.vec[X])
		line.step[X] = 1;
	else
		line.step[X] = -1;
	if (a.vec[Y] < b.vec[Y])
		line.step[Y] = 1;
	else
		line.step[Y] = -1;
	line.x = a.vec[X];
	line.y = a.vec[Y];
	line.points[0] = a.vec;
	line.points[1] = b.vec;
	return (line);
}

void	draw_line(mlx_image_t *img, t_point a, t_point b, t_fdf *data)
{
	t_line	line;
	int32_t	error;

	line = get_line_info(a, b);
	init_line_cols(data, line.colours, a, b);
	error = (int32_t) line.delta[X] - (int32_t) line.delta[Y];
	while (true)
	{
		if (in_bounds(img, &line))
			mlx_put_pixel(img, line.x, line.y, inter_colours(&line));
		if (line.x == line.points[1][X] && line.y == line.points[1][Y])
			return ;
		if (error >= 0)
		{
			line.x += line.step[X];
			error -= (int32_t) line.delta[Y];
		}
		if (error < 0)
		{
			line.y += line.step[Y];
			error += (int32_t) line.delta[X];
		}
	}
}
