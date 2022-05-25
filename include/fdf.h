/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 17:01:03 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/20 17:01:03 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720
# define DEFAULT_COLOUR	0xFFFFFFFF
# include "colour.h"
# include "MLX42/MLX42.h"
# define ERR_ARGS		"Error: Not enough arguments\nUsage: ./fdf <map_file>"
# define ERR_MAP_PARSE	"Error: Map parsing failed"
# define ERR_MAP_VALID	"Error: Invalid map!"
# define ERR_MAL_TITLE	"Error: Failed to allocate title"
# define ERR_MLX_INIT	"Error: MLX failed to initialize"
# define ERR_MLX_IMG	"Error: Could not create image"

typedef int32_t	t_ivec __attribute__ ((vector_size (4 * sizeof(int32_t))));

/**
 * Enum for indices in t_dvec's.
 * W is the axis of rotation for rotation quaternions.
 */
typedef enum e_axis {
	X,
	Y,
	Z,
	W
}	t_axis;

typedef struct s_point {
	t_ivec	vec;
	int32_t	orig_z;
	t_rgba	colour;
}	t_point;

typedef struct s_line {
	int32_t		x;
	int32_t		y;
	uint32_t	delta[2];
	int8_t		step[2];
	t_hsva		colours[2];
	t_ivec		points[2];
}	t_line;

typedef struct s_map {
	t_point		***points;
	uint32_t	max_x;
	uint32_t	max_y;
	int32_t		max_z;
	int32_t		min_z;
}	t_map;

typedef double	t_dvec __attribute__ ((vector_size (4 * sizeof(double))));
typedef t_dvec	t_dmat[4];

typedef enum e_col_mode {
	DEFAULT,
	HEIGHT,
	GREYS,
	END
}	t_col;

typedef struct s_cam {
	int32_t		scale;
	double		z_scale;
	t_dvec		angles;
	t_dvec		old_angles;
	t_dvec		rot_q;
	t_dmat		matrix;
	t_ivec		focal;
	t_ivec		offset;
}	t_cam;

typedef struct s_fdf {
	char		*title;
	t_map		map;
	t_cam		cam;
	t_col		col;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_fdf;

typedef struct s_axis_info {
	t_axis	axis;
	bool	decrement;
}	t_axis_info;

/*
 * Init functions
 */
void		init_map(t_fdf *data, const char *map);
bool		parse(t_map *map, const char *file);
void		init_mlx(t_fdf *data, const char *map);

/*
 * Hooks
 */
void		key_event(mlx_key_data_t e, void *param);
void		scroll_event(double xdelta, double ydelta, void *param);
void		resize_event(int32_t width, int32_t height, void *param);

/*
 * Draw functions
 */
void		render(t_fdf *data);
void		update_rotation(t_cam *cam);
void		draw_line(mlx_image_t *img, t_point a, t_point b, t_fdf *data);
void		init_line_cols(t_fdf *data, t_hsva cols[2], t_point a, t_point b);
uint32_t	inter_colours(t_line *line);

/*
 * Cam functions
 */
void		reset_cam(t_fdf *data);
void		rotate_cam(t_cam *cam, keys_t key, bool modifier);
void		translate_cam(t_cam *cam, keys_t key, bool modifier);
void		zscale_cam(t_cam *cam, bool dec, bool modifier);
t_dvec		init_isometric_quaternion(void);

/*
 * Matrix/vector functions
 */
void		identity_matrix(t_dmat matrix);
t_dvec		ivec_to_dvec(t_ivec ivec);
t_ivec		dvec_to_ivec(t_dvec dvec);
t_dvec		mult_vec(t_dmat matrix, t_dvec vector);

/*
 * The most important function of all
 */
void		error(t_fdf *data, char *reason, bool in_lib);

#endif