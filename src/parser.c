/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 16:47:58 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/20 16:47:58 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static t_point	*create_point(char *str)
{
	t_point			*point;
	char			**strs;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	strs = ft_split(str, ',');
	if (!strs || !strs[0] || *strs[0] == '\0' || *strs[0] == '\n')
	{
		free(point);
		return (NULL);
	}
	point->vec[Z] = ft_atoi(strs[0]);
	if (strs[1])
		point->colour = get_rgba((ft_hextoui(strs[1]) << 8u) | 0xFFu);
	else
		point->colour = get_rgba(DEFAULT_COLOUR);
	ft_free_mult((void **) strs);
	return (point);
}

static t_point	***parse_fd(int fd, int i)
{
	t_point	***ret;
	t_point	**line_points;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_calloc(i + 1, sizeof(t_point **)));
	line_points = (t_point **) ft_split_map(line, ' ',
			(void *(*)(char *)) create_point, free);
	free(line);
	if (!line_points)
		return (NULL);
	ret = parse_fd(fd, i + 1);
	if (ret == NULL)
		ft_free_mult((void *) line_points);
	else
		ret[i] = line_points;
	return (ret);
}

static bool	init_map_data(t_map *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	map->min_z = INT32_MAX;
	map->max_z = INT32_MIN;
	while (map->points[y])
	{
		x = 0;
		while (map->points[y][x])
		{
			map->points[y][x]->vec[X] = (int32_t) x;
			map->points[y][x]->vec[Y] = (int32_t) y;
			map->min_z = ft_min(map->points[y][x]->vec[Z], map->min_z);
			map->max_z = ft_max(map->points[y][x]->vec[Z], map->max_z);
			++x;
		}
		if (map->max_x == 0)
			map->max_x = x - 1;
		else if (map->max_x != x - 1)
			return (false);
		++y;
	}
	map->max_y = y - 1;
	return (true);
}

bool	parse(t_map *map, const char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	map->points = parse_fd(fd, 0);
	close(fd);
	if (!map->points)
		return (false);
	return (init_map_data(map));
}
