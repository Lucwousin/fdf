/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 13:49:13 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/23 13:49:13 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOUR_H
# define COLOUR_H
# include <stdint.h>

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

t_rgba	get_rgba(uint32_t hex);
t_hsva	rgba_to_hsva(t_rgba rgb);
t_rgba	hsva_to_rgba(t_hsva hsv);
void	normalize_hsva(t_hsva *a, t_hsva *b);

#endif
