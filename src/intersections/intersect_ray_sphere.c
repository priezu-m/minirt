/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_sphere.c                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 09:17:38                                            */
/*   Updated:  2023/11/14 18:23:25                                            */
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

t_intersection	intersect_ray_sphere(t_vector ray_direction, t_vector origin,
					t_sphere sphere)
{
	const t_vector		oc = substract(origin, sphere.center);
	const long double	b = 2.0L * dot_product(oc, ray_direction);
	const long double	c = dot_product(oc, oc) - powl(sphere.diameter / 2, 2);
	long double			distance[2];
	t_intersection		intersection;

	intersection.distance = -1;
	if ((b * b - 4 * c) < 0)
		return (intersection);
	distance[0] = (-b - sqrtl(b * b - 4 * c)) / 2.0L;
	distance[1] = (-b + sqrtl(b * b - 4 * c)) / 2.0L;
	if (((distance[0] < distance[1]) || (distance[1] < 0)) && distance[0] >= 0)
		intersection.distance = distance[0];
	if (isnan(distance[1]) == false)
		intersection.distance = distance[1];
	intersection.point = add(origin, multiply(ray_direction, distance[0]));
	intersection.surface_normal = normalize(substract(intersection.point,
				sphere.center));
	return (intersection);
}

#pragma clang diagnostic pop
