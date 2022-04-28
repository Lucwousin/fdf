/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucas <lucas@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 13:55:02 by lucas         #+#    #+#                 */
/*   Updated: 2022/04/22 13:55:02 by lucas         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static bool	in_bounds(mlx_image_t *img, t_line *line)
{
	int	x;
	int	y;

	x = line->x;
	y = line->y;
	if (x >= 0 && y >= 0)
		if ((uint32_t) x < img->width && (uint32_t) y < img->height)
			return (true);
	return (false);
}

static double	calculate_progress(t_point a, t_point b, t_line *line)
{
	if (line->dx >= line->dy)
	{
		if (line->x == a.x)
			return (0.0);
		else if (line->x == b.x)
			return (1.0);
		else
			return abs(line->x - a.x) / (double) (line->dx);
	}
	else
	{
		if (line->y == a.y)
			return (0.0);
		else if (line->y == b.y)
			return (1.0);
		else
			return abs(line->y - a.y) / (double) (line->dy);
	}
}

uint32_t	intrpl_col(t_point a, t_point b, t_line *line)
{
	double	progress;
	t_hsva	colour;
	
	if (a.colour.colour == b.colour.colour)
		return (a.colour.colour);
	progress = calculate_progress(a, b, line);
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


t_line	get_line_info(t_point a, t_point b)
{
	t_line	line;
	
	line.dx = ft_abs(b.x - a.x);
	line.dy = ft_abs(b.y - a.y);
	if (a.x < b.x)
		line.x_step = 1;
	else
		line.x_step = -1;
	if (a.y < b.y)
		line.y_step = 1;
	else
		line.y_step = -1;
	line.x = a.x;
	line.y = a.y;
	line.colour_a = rgba_to_hsva(a.colour);
	line.colour_b = rgba_to_hsva(b.colour);
	normalize_colours(&line.colour_a, &line.colour_b);
	return (line);
}

void	draw_line(mlx_image_t *img, t_point a, t_point b)
{
	t_line	line;
	int		error;

	line = get_line_info(a, b);
	error = 2 * (line.dx - line.dy);
	while (true)
	{
		if (in_bounds(img, &line))
			mlx_put_pixel(img, line.x, line.y, intrpl_col(a, b, &line));
		if (line.x == b.x && line.y == b.y)
			return ;
		if (error >= 0)
		{
			line.x += line.x_step;
			error -= 2 * line.dy;
		}
		if (error < 0)
		{
			line.y += line.y_step;
			error += 2 * line.dx;
		}
	}
}