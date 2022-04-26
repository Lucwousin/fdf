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