/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucas <lucas@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 17:01:03 by lucas         #+#    #+#                 */
/*   Updated: 2022/04/20 17:01:03 by lucas         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720
# define DEFAULT_COLOUR	0xFFFFFFFF
# include "MLX42/MLX42.h"

typedef union u_rgba {
	uint32_t	colour;
	struct s_rgba {
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	} rgba;
}	t_rgba;

typedef struct s_hsva {
	double	h;
	double	s;
	double	v;
	uint8_t	a;
}	t_hsva;

typedef struct s_point {
	int		x;
	int		y;
	int		z;
	t_rgba	colour;
}	t_point;

typedef struct s_line {
	int			x;
	int			y;
	uint32_t	dx;
	uint32_t	dy;
	int8_t		x_step;
	int8_t		y_step;
	t_hsva		colour_a;
	t_hsva		colour_b;
}	t_line;

typedef struct s_map {
	t_point	***points;
	int		max_x;
	int		max_y;
	int		max_z;
	int		min_z;
}	t_map;

typedef struct s_cam {
	double	pitch;
	double	yaw;
	double	roll;
	int		scale;
	double	z_scale;
	t_point	focal;
	t_point	offset;
}	t_cam;

typedef struct s_fdf {
	char		*title;
	t_map		map;
	t_cam		cam;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_fdf;

bool	parse(t_map *map, const char *file);
void	render(t_fdf *data);
void	draw_line(mlx_image_t *img, t_point a, t_point b);
void	reset_cam(t_fdf *data);

t_rgba	get_rgba(uint32_t hex);
t_hsva	rgba_to_hsva(t_rgba rgb);
t_rgba	hsva_to_rgba(t_hsva hsv);
void	normalize_colours(t_hsva *a, t_hsva *b);

void	subtract(t_point *a, t_point *b);

void	key_event(mlx_key_data_t event, void *param);
void	scroll_event(double xdelta, double ydelta, void *param);
void	resize_event(int32_t width, int32_t height, void *param);

void	cleanup_map(t_map *map);

#endif