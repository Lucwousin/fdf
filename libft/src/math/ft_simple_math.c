/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_simple_math.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <stdint.h>

int32_t	ft_min(int32_t a, int32_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int32_t	ft_max(int32_t a, int32_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int32_t	ft_abs(int32_t n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

int32_t	ft_clamp(int32_t val, int32_t min, int32_t max)
{
	return (ft_max(min, ft_min(max, val)));
}
