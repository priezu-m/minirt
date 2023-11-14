/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_plane.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/11/10 15:42:08                                            */
/*   Updated:  2023/11/14 18:23:46                                            */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

t_intersection	intersect_ray_plane(t_vector ray_direction, t_vector origin,
					t_plane plane)
{
	const t_vector		x = substract(origin, plane.position);
	const long double	dv = dot_product(ray_direction, plane.normal);
	const long double	t = dot_product(multiply(x, -1), plane.normal) / dv;
	const t_vector		point = add(origin, multiply(ray_direction, t));

	if (t < 0)
		return ((t_intersection){.distance = -1});
	if (dv < 0)
		return ((t_intersection){.distance = t, .point = point,
			.surface_normal = multiply(plane.normal, -1)});
	return ((t_intersection){.distance = t, .point = point,
		.surface_normal = plane.normal});
}

#pragma clang diagnostic pop
