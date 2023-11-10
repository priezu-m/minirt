/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_sphere.c                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 09:17:38                                            */
/*   Updated:  2023/11/09 19:13:11                                            */
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

long double	intersect_ray_sphere(t_vector3 ray_direction, t_vector3 origin,
				t_sphere sphere)
{
	t_intersections		intersections = {0};
	const t_vector3		oc = vector3_substract(origin, sphere.position);
	const long double	b = 2.0L * dot_product_vector3(oc, ray_direction);
	const long double	c = dot_product_vector3(oc, oc)
							- powl(sphere.diameter / 2.L, 2.L);
	const long double	discriminant = b * b - 4 * c;

	if (discriminant < 0)
		return (-1);
	intersections.t1 = (-b - sqrtl(discriminant)) / 2.0L;
	intersections.t2 = (-b + sqrtl(discriminant)) / 2.0L;
	if (((intersections.t1 < intersections.t2) || (intersections.t2 < 0)) && intersections.t1 >= 0)
		return (intersections.t1);
	if (isnan(intersections.t2) == false)
		return (intersections.t2);
	return (-1);
}

#pragma clang diagnostic pop
