/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 20:03:15 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/28 20:03:15 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>
#define DEG_60	0.16666666666666666

t_rgba	get_rgba(uint32_t hex)
{
	t_rgba	rgba;

	rgba.colour = hex;
	return (rgba);
}

/**
 * Convert rgba colour to hsva colour.
 * 
 * R, G, B, A are in range 0x00 - 0xFF
 * H, S, V, A are in range 0.0 - 1.0
 * 
 * HSV can be visualized as a conic shape, with the point being black and 
 * the center of the top circle white. A circular rainbow is around the circle
 * with red at 0 (or 360) degrees, green at 120 degrees, and blue at 240.
 * 
 * The hue is the angle on the circle
 * if hue is 0.0 or 1.0 the colour is red, 0.3333 green, 0.6666 blue.
 * This means you can split the circle up in 3 parts.
 * Red dominant:	300 deg -  60 deg
 * Green dominant:	 60 deg - 180 deg
 * Blue dominant:	180 deg - 300 deg
 * If red is dominant (ie, the highest value in rgb) this means we're somewhere
 * in the red part of the circle. We can know the exact hue by calculating how
 * big of a part the other 2 colours play - relative to each other.
 * Examples:
 * For (100, 50, 50) the hue would be 0.0, as red is dominant and green and
 * blue are exactly the same.
 * For (125, 75, 50) the hue would be 1/18, as red is dominant, and the
 * difference between green and blue is 1/3 of the difference between rgb
 * max and min and the parts where colours exist are 60 degrees (1/6) big.
 * (1/18 = 1/3 * 1/6).
 * For (50, 250, 0): 2/6 + 1/6 * (-50 / (250 - 0)) = 2/6 - 1/5 * 1/6 =..
 * 10/30 - 1/30 = 3/10
 * 
 * The saturation is how far away from the center we are.
 * If it's 0, colour is white, if it's 1, the colour is bright.
 * This is equal to 1 minus the percentage difference of the min and max rgb
 * For example, for (100, 100, 75) this would be 0.25 (which is unsaturated)
 * 
 * The value is how "strong" the colour is; this is the max rgb value.
 * A value of 0 is black.
 * 
 * (http://color.lukas-stratmann.com/color-systems/hsv.html)
 */
t_hsva	rgba_to_hsva(t_rgba rgb)
{
	t_hsva	hsv;
	uint8_t	rgb_min;
	uint8_t	rgb_max;
	uint8_t	rgb_delta;

	ft_bzero(&hsv, sizeof(t_hsva));
	rgb_min = ft_min(ft_min(rgb.rgba.r, rgb.rgba.g), rgb.rgba.b);
	rgb_max = ft_max(ft_max(rgb.rgba.r, rgb.rgba.g), rgb.rgba.b);
	hsv.a = rgb.rgba.a;
	if (rgb_max == 0)
		return (hsv);
	hsv.v = rgb_max / 255.0;
	rgb_delta = rgb_max - rgb_min;
	if (rgb_delta == 0)
		return (hsv);
	hsv.s = rgb_delta / (double) rgb_max;
	if (rgb_max == rgb.rgba.r)
		hsv.h = DEG_60 * (0 + (rgb.rgba.g - rgb.rgba.b) / (double)(rgb_delta));
	else if (rgb_max == rgb.rgba.g)
		hsv.h = DEG_60 * (2 + (rgb.rgba.b - rgb.rgba.r) / (double)(rgb_delta));
	else
		hsv.h = DEG_60 * (4 + (rgb.rgba.r - rgb.rgba.g) / (double)(rgb_delta));
	return (hsv);
}

/**
 * Get rgb values from the hsv values (duh).
 * 
 * Major is the major rgb value - the one with the highest value.
 * Minor is the second biggest of the rgb value.
 * Other is the rgb value that's only dependent on the saturation.
 */
static void	set_rgb(t_hsva hsv, uint8_t *major, uint8_t *minor, uint8_t *other)
{
	uint8_t	rgb_max;
	uint8_t	rgb_min;
	uint8_t	rgb_delta;

	rgb_max = hsv.v * 0xFF;
	rgb_delta = hsv.s * rgb_max;
	rgb_min = rgb_max - rgb_delta;
	*major = rgb_max;
	*other = rgb_min;
	*minor = rgb_min + fmod(hsv.h, DEG_60) * rgb_delta;
}

t_rgba	hsva_to_rgba(t_hsva hsv)
{
	t_rgba	rgb;
	uint8_t	section;

	rgb.rgba.a = hsv.a;
	if (hsv.v == 0.0)
		return (get_rgba(rgb.rgba.a));
	section = hsv.h / DEG_60;
	if (section < 1)
		set_rgb(hsv, &rgb.rgba.r, &rgb.rgba.g, &rgb.rgba.b);
	else if (section >= 1 && section < 2)
		set_rgb(hsv, &rgb.rgba.g, &rgb.rgba.r, &rgb.rgba.b);
	else if (section >= 2 && section < 3)
		set_rgb(hsv, &rgb.rgba.g, &rgb.rgba.b, &rgb.rgba.r);
	else if (section >= 3 && section < 4)
		set_rgb(hsv, &rgb.rgba.b, &rgb.rgba.g, &rgb.rgba.r);
	else if (section >= 4 && section < 5)
		set_rgb(hsv, &rgb.rgba.b, &rgb.rgba.r, &rgb.rgba.g);
	else if (section >= 5 && section < 6)
		set_rgb(hsv, &rgb.rgba.r, &rgb.rgba.b, &rgb.rgba.g);
	return (rgb);
}
