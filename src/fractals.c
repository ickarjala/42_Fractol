/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 02:04:07 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/13 22:25:04 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline double	z_burning_ship(t_cx z, t_cx c)
{
	return (fabs(2 * z.x * z.y) + c.y);
}

static inline double	z_tricorn(t_cx z, t_cx c)
{
	return (-2 * z.x * z.y + c.y);
}

static inline double	z_mandelbrot(t_cx z, t_cx c)
{
	return (2 * z.x * z.y + c.y);
}

static inline double	choose_z(t_cx z, t_cx c, int n)
{
	if (n == 1)
		return (z_mandelbrot (z, c));
	else if (n == 2)
		return (z_tricorn (z, c));
	else if (n == 3)
		return (z_burning_ship (z, c));
	return (z_mandelbrot (z, c));
}

/* Return a sample indicating whether point c in the complex plane
 * falls inside the Mandelbrot Set, namely how many iterations it took
 *
 * Escape time algorithm: z2 n(c) = z2 + c
 * z = iterating complex, using its own (R,i == x,y) as input
 * z2 = z squared
 * c = complex constant, gets added to z every iteration
*/
int	mandelbrot(t_cx z, t_cx c)
//int	julia(t_cx z, t_cx c)
{
	t_cx	z2;
	t_cx	old;
	int		period;
	int		n;

	z2 = (t_cx){z.x * z.x, z.y * z.y};
	old = z2;
	period = 0;
	n = -1;
	while (++n < MAX_DEPTH && z2.x + z2.y <= 4.0L)
	{
		z.y = choose_z (z, c, 3);
		z.x = z2.x - z2.y + c.x;
		z2 = (t_cx){z.x * z.x, z.y * z.y};
		if (z2.x == old.x && z2.y == old.y)
			return (MAX_DEPTH);
		period ++;
		if (period > PERIOD)
		{
			old = z2;
			period = 0;
		}
	}
	return (n);
}

// TODO: remember to make this back into inline!
// TODO: add dispatch table / if branches (might be faster idk)
