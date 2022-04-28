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

static void	set_line_info(t_point a, t_point b, t_point *delt, t_point *step)
{
	delt->x = ft_abs(b.x - a.x);
	delt->y = ft_abs(b.y - a.y);
	if (a.x < b.x)
		step->x = 1;
	else
		step->x = -1;
	if (a.y < b.y)
		step->y = 1;
	else
		step->y = -1;
}

static bool	in_bounds(mlx_image_t *img, t_point p)
{
	int	x;
	int	y;

	x = p.x;
	y = p.y;
	if (x >= 0 && y >= 0)
		if ((uint32_t) x < img->width && (uint32_t) y < img->height)
			return (true);
	return (false);
}

static double	calculate_progress(t_point a, t_point b, t_point delta, t_point cur)
{
	if (delta.x >= delta.y)
	{
		if (cur.x == a.x)
			return (0.0);
		else if (cur.x == b.x)
			return (1.0);
		else
			return abs(cur.x - a.x) / (double) (delta.x);
	}
	else
	{
		if (cur.y == a.y)
			return (0.0);
		else if (cur.y == b.y)
			return (1.0);
		else
			return abs(cur.y - a.y) / (double) (delta.y);
	}
}

uint32_t	intrpl_col(t_point a, t_point b, t_point delta, t_point cur)
{
	double	progress;
	t_hsva	hsv_a;
	t_hsva	hsv_b;
	t_hsva	hsv_cur;
	
	if (a.colour.colour == b.colour.colour)
		return (a.colour.colour);
	progress = calculate_progress(a, b, delta, cur);
	if (progress == 0.0)
		return (a.colour.colour);
	else if (progress == 1.0)
		return (b.colour.colour);
	hsv_a = rgba_to_hsva(a.colour);
	hsv_b = rgba_to_hsva(b.colour);
	if (hsv_a.v == 0)
	{
		hsv_a.h = hsv_b.h;
		hsv_a.s = hsv_b.s;
	}
	else if (hsv_b.v == 0)
	{
		hsv_b.h = hsv_a.h;
		hsv_b.s = hsv_a.s;
	}
	else if (hsv_a.s == 0)
		hsv_a.h = hsv_b.h;
	else if (hsv_b.s == 0)
		hsv_b.h = hsv_a.h;
	hsv_cur.h = hsv_a.h + (hsv_b.h - hsv_a.h) * progress;
	hsv_cur.s = hsv_a.s + (hsv_b.s - hsv_a.s) * progress;
	hsv_cur.v = hsv_a.v + (hsv_b.v - hsv_a.v) * progress;
	hsv_cur.a = hsv_a.a + (hsv_b.a - hsv_a.a) * progress;
	return (hsva_to_rgba(hsv_cur).colour);
}

void	draw_line(mlx_image_t *img, t_point a, t_point b)
{
	t_point	delt;
	t_point	step;
	t_point	cur;
	int		error;

	set_line_info(a, b, &delt, &step);
	error = 2 * (delt.x - delt.y);
	cur = a;
	while (true)
	{
		if (in_bounds(img, cur))
			mlx_put_pixel(img, cur.x, cur.y, intrpl_col(a, b, delt, cur));
		if (cur.x == b.x && cur.y == b.y)
			return ;
		if (error >= 0)
		{
			cur.x += step.x;
			error -= 2 * delt.y;
		}
		if (error < 0)
		{
			cur.y += step.y;
			error += 2 * delt.x;
		}
	}
}