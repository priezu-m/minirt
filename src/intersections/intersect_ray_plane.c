/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_plane.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/11/10 15:42:08                                            */
/*   Updated:  2023/11/10 16:20:41                                            */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"


long double	intersect_ray_plane(t_vector3 ray_direction, t_vector3 origin, t_plane plane)
{

	t_vector3	x = vector3_substract(origin, plane.position);
	long double	dv = dot_product_vector3(ray_direction, plane.orientation_vector);

	if (dv < 0)
		return (-1);
	return (dot_product_vector3(vector3_multiply(x, -1), plane.orientation_vector) / dv);
}

#pragma clang diagnostic pop
