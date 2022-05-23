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

static double	calculate_progress(t_ivec a, t_ivec b, t_line *line)
{
	if (line->dx >= line->dy)
	{
		if (line->x == a[X])
			return (0.0);
		if (line->x == b[X])
			return (1.0);
		return (abs(line->x - a[X]) / (double)(line->dx));
	}
	else
	{
		if (line->y == a[Y])
			return (0.0);
		if (line->y == b[Y])
			return (1.0);
		return (abs(line->y - a[Y]) / (double)(line->dy));
	}
}

static uint32_t	get_colour(t_point a, t_point b, t_line *line)
{
	double	progress;
	t_hsva	colour;

	if (a.colour.colour == b.colour.colour)
		return (a.colour.colour);
	progress = calculate_progress(a.vec, b.vec, line);
	if (progress == 0.0)
		return (a.colour.colour);
	else if (progress == 1.0)
		return (b.colour.colour);
	colour.h = ft_interpolate_d(line->colour_a.h, line->colour_b.h, progress);
	colour.s = ft_interpolate_d(line->colour_a.s, line->colour_b.s, progress);
	colour.v = ft_interpolate_d(line->colour_a.v, line->colour_b.v, progress);
	colour.a = ft_interpolate_i(line->colour_a.a, line->colour_b.a, progress);
	return (hsva_to_rgba(colour).colour);
}

static t_line	get_line_info(t_point a, t_point b)
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
	line.colour_a = rgba_to_hsva(a.colour);
	line.colour_b = rgba_to_hsva(b.colour);
	normalize_hsva(&line.colour_a, &line.colour_b);
	return (line);
}

void	draw_line(mlx_image_t *img, t_point a, t_point b)
{
	t_line	line;
	int32_t	error;

	line = get_line_info(a, b);
	error = (int32_t) line.dx - (int32_t) line.dy;
	while (true)
	{
		if (in_bounds(img, &line))
			mlx_put_pixel(img, line.x, line.y, get_colour(a, b, &line));
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
