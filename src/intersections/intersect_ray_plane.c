/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_plane.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/11/10 15:42:08                                            */
/*   Updated:  2023/11/10 19:35:42                                            */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

long double	intersect_ray_plane(t_vector ray_direction, t_vector origin,
				t_plane plane)
{
	const t_vector		x = substract(origin, plane.position);
	const long double	dv = dot_product(ray_direction, plane.normal);

	if (dv < 0)
		return (-1);
	return (dot_product(multiply(x, -1), plane.normal) / dv);
}

#pragma clang diagnostic pop
