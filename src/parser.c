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
	if (!strs || !strs[0] || *strs[0] == '\0')
	{
		free(point);
		return (NULL);
	}
	point->vec[Z] = ft_atoi(strs[0]);
	point->height = point->vec[Z];
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
	char	*trimmed;

	line = get_next_line(fd);
	if (!line)
		return (ft_calloc(i + 1, sizeof(t_point **)));
	trimmed = ft_strtrim(line, " \n");
	free(line);
	if (!trimmed)
		return (NULL);
	line_points = (t_point **) ft_split_map(trimmed, ' ',
			(void *(*)(char *)) create_point, free);
	free(trimmed);
	if (!line_points)
		return (NULL);
	ret = parse_fd(fd, i + 1);
	if (ret == NULL)
		ft_free_mult((void *) line_points);
	else
		ret[i] = line_points;
	return (ret);
}

bool	parse(t_map *map, const char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	map->points = parse_fd(fd, 0);
	close(fd);
	return (map->points != NULL);
}
