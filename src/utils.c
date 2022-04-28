/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucas <lucas@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 12:16:46 by lucas         #+#    #+#                 */
/*   Updated: 2022/04/22 12:16:46 by lucas         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	subtract(t_point *a, t_point *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

void	cleanup_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->points[i])
		ft_free_mult((void **) map->points[i++]);
	free(map->points);
}

/**
 * Initialize hue and saturation data from the other colour
 * So that we do not always start with hue 0 if value or saturation was 0
 */
void	normalize_colours(t_hsva *a, t_hsva *b)
{
	if (a->v == 0)
	{
		a->h = b->h;
		a->s = b->s;
	}
	else if (b->v == 0)
	{
		b->h = a->h;
		b->s = a->s;
	}
	else if (a->s == 0)
		a->h = b->h;
	else if (b->s == 0)
		b->h = a->h;
}
