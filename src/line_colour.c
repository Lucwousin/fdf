/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_colour.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 14:31:42 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/24 14:31:42 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"
#include "libft.h"

static t_hsva	colour_from_height(t_point p, t_fdf *data)
{
	const t_hsva	white = (t_hsva){0.0, 0.0, 1.0, 0xFF};
	t_hsva			colour;
	double			delta_z;
	double			height_fraction;

	delta_z = data->map.max_z - data->map.min_z;
	if (delta_z == 0)
		return (white);
	height_fraction = (p.orig_z - data->map.min_z) / delta_z;
	colour.h = 5 / 6.0 - (5 / 6.0) * height_fraction;
	colour.s = 1.0;
	colour.v = 1.0;
	colour.a = 0xFF;
	return (colour);
}

void	init_line_colours(t_fdf *data, t_hsva cols[2], t_point a, t_point b)
{
	if (data->col == DEFAULT)
	{
		cols[0] = rgba_to_hsva(a.colour);
		cols[1] = rgba_to_hsva(b.colour);
	}
	else
	{
		cols[0] = colour_from_height(a, data);
		cols[1] = colour_from_height(b, data);
		if (data->col == GREYS)
		{
			cols[0].v = 1 - cols[0].h;
			cols[1].v = 1 - cols[1].h;
			cols[0].s = 0;
			cols[1].s = 0;
		}
	}
	normalize_hsva(cols + 0, cols + 1);
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

uint32_t	inter_line_colour(t_point a, t_point b, t_line *line)
{
	double	progress;
	t_hsva	colour;

	progress = calculate_progress(a.vec, b.vec, line);
	if (progress == 0.0)
		return (hsva_to_rgba(line->colours[0]).colour);
	else if (progress == 1.0)
		return (hsva_to_rgba(line->colours[1]).colour);
	colour.h = ft_interpolate_d(line->colours[0].h, line->colours[1].h, progress);
	colour.s = ft_interpolate_d(line->colours[0].s, line->colours[1].s, progress);
	colour.v = ft_interpolate_d(line->colours[0].v, line->colours[1].v, progress);
	colour.a = ft_interpolate_i(line->colours[0].a, line->colours[1].a, progress);
	return (hsva_to_rgba(colour).colour);
}