/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_sphere.c                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 09:17:38                                            */
/*   Updated:  2023/11/10 19:38:34                                            */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"
#include <math.h>
#include <stdbool.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

long double	intersect_ray_sphere(t_vector ray_direction, t_vector origin,
				t_sphere sphere)
{
	const t_vector		oc = substract(origin, sphere.center);
	const long double	b = 2.0L * dot_product(oc, ray_direction);
	const long double	c = dot_product(oc, oc)
		- powl(sphere.diameter / 2.L, 2.L);
	long double			distance1;
	long double			distance2;

	if ((b * b - 4 * c) < 0)
		return (-1);
	distance1 = (-b - sqrtl(b * b - 4 * c)) / 2.0L;
	distance2 = (-b + sqrtl(b * b - 4 * c)) / 2.0L;
	if (((distance1 < distance2) || (distance2 < 0)) && distance1 >= 0)
		return (distance1);
	if (isnan(distance2) == false)
		return (distance2);
	return (-1);
}

#pragma clang diagnostic pop
