#include "fdf.h"
#include "libft.h"
#include <math.h>
#define DEG_60	42.5

/*static double	get_rgb_part(unsigned char angle, double h, double s, double v)
{
	double	colour;
	double	k;

	k = fmod(angle + 6 * h, 6);
	colour = v - (v * s)

}*/

t_rgba	get_rgba(uint32_t hex)
{
	t_rgba	rgba;

	rgba.r = hex >> 24 & 0xFF;
	rgba.g = hex >> 16 & 0xFF;
	rgba.b = hex >> 8 & 0xFF;
	rgba.a = hex & 0xFF;
	return (rgba);
}

t_hsva	rgba_to_hsva(t_rgba rgb)
{
	t_hsva			hsv;
	unsigned char	rgb_min;
	unsigned char	rgb_max;

	ft_bzero(&hsv, sizeof(t_hsva));
	rgb_min = ft_min(rgb.r, rgb.g);
	rgb_min = ft_min(rgb.b, rgb_min);
	rgb_max = ft_max(rgb.r, rgb.g);
	rgb_max = ft_max(rgb.b, rgb_max);
	hsv.a = rgb.a;
	hsv.v = rgb_max;
	if (hsv.v == 0)
		return (hsv);
	hsv.s = 0xFF * (unsigned int) (rgb_max - rgb_min) / rgb_max;
	if (hsv.s == 0)
		return (hsv);
	if (rgb_max == rgb.r)
		hsv.h = DEG_60 * (0 + (rgb.g - rgb.b) / (double) (rgb_max - rgb_min));
	else if (rgb_max == rgb.g)
		hsv.h = DEG_60 * (2 + (rgb.b - rgb.r) / (double) (rgb_max - rgb_min));
	else
		hsv.h = DEG_60 * (4 + (rgb.r - rgb.g) / (double) (rgb_max - rgb_min));
	return (hsv);
}
/*

t_rgba	hsva_to_rgba(t_hsva hsv)
{
	t_rgba			rgb;
	double			h;
	double			s;
	double			v;

	rgb.a = hsv.a;
	if (hsv.s == 0)
	{
		ft_memset(&rgb, hsv.v, sizeof(t_rgba));
		return (rgb);
	}
	h = hsv.h / (double) 255;
	s = hsv.s / (double) 255;
	v = hsv.v / (double) 255;
	rgb.r = (unsigned char) (255 * get_rgb_part(5, h, s, v));
	rgb.g = (unsigned char) (255 * get_rgb_part(1, h, s, v));
	rgb.b = (unsigned char) (255 * get_rgb_part(3, h, s, v));
}*/
