/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 18:16:53 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/19 18:16:53 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>

void	reset_matrix(t_dmat matrix)
{
	const t_dmat	identity = {
		(t_dvec){1.0, 0.0, 0.0, 0.0},
		(t_dvec){0.0, 1.0, 0.0, 0.0},
		(t_dvec){0.0, 0.0, 1.0, 0.0}
	};

	matrix[0] = identity[0];
	matrix[1] = identity[1];
	matrix[2] = identity[2];
}

t_dvec	ivec_to_dvec(t_ivec ivec)
{
	return ((t_dvec){
		ivec[0],
		ivec[1],
		ivec[2],
		0
	});
}

t_ivec	dvec_to_ivec(t_dvec dvec)
{
	return ((t_ivec){
		(int32_t) round(dvec[0]),
		(int32_t) round(dvec[1]),
		(int32_t) round(dvec[2]),
		0
	});
}

t_dvec	mult_vec(t_dmat matrix, t_dvec vector)
{
	return ((t_dvec){
		vector[X] * matrix[X][0] +
		vector[Y] * matrix[X][1] +
		vector[Z] * matrix[X][2],
		vector[X] * matrix[Y][0] +
		vector[Y] * matrix[Y][1] +
		vector[Z] * matrix[Y][2],
		vector[X] * matrix[Z][0] +
		vector[Y] * matrix[Z][1] +
		vector[Z] * matrix[Z][2]
	});
}
