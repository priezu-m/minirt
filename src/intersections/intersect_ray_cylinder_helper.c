/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_cylinder_helper.c                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/11/14 18:34:34                                            */
/*   Updated:  2023/11/14 19:35:10                                            */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static t_intersection	get_intesection_from_distance(long double distance,
							t_vector origin, t_vector ray_direction,
							t_cylinder cylinder)
{
	const t_vector	lid_center = add(cylinder.geometric_center,
			multiply(cylinder.direction, -cylinder.height / 2.0L));
	long double		m;
	t_vector		normal;
	t_vector		point;

	point = add(origin, multiply(ray_direction, distance));
	m = dot_product(ray_direction, cylinder.direction) * distance;
	m += dot_product(substract(origin, lid_center), cylinder.direction);
	normal = normalize(substract(point, add(lid_center,
					multiply(cylinder.direction, m))));
	return ((t_intersection){.point = point, .surface_normal = normal,
		.distance = distance});
}

static t_intersection	intersect_ray_cylinder_helper_internal(
		t_intersect_ray_cylinder_data data)
{
	if (data.distance[1] >= 0
		&& ((data.distance[1] < data.intersections[0].distance)
			|| (data.intersections[0].distance < 0))
		&& ((data.distance[1] < data.intersections[1].distance)
			|| (data.intersections[1].distance < 0)))
		return (get_intesection_from_distance(data.distance[1], data.origin,
				data.ray_direction, data.cylinder));
	if ((data.intersections[0].distance >= 0)
		&& ((data.intersections[0].distance < data.intersections[1].distance)
			|| (data.intersections[1].distance < 0)))
		return (data.intersections[0]);
	return (data.intersections[1]);
}

t_intersection	intersect_ray_cylinder_helper(
		t_intersect_ray_cylinder_data data)
{
	data.distance[1] = (-data.discriminant.b + sqrtl(data.discriminant.bb_4ac))
		/ (2.0L * data.discriminant.a);
	data.m = dot_product(data.ray_direction, data.cylinder.direction)
		* data.distance[1];
	data.m += dot_product(substract(data.origin, data.lid_center),
			data.cylinder.direction);
	if (data.m > data.cylinder.height || data.m < 0 || isnan(data.m) == true)
	{
		data.distance[1] = -1;
		data.intersections[1] = check_intersection_whit_lid(data.ray_direction,
				data.origin, data.cylinder);
	}
	if ((data.distance[0] >= 0) && ((data.distance[0] < data.distance[1])
			|| (data.distance[1] < 0))
		&& ((data.distance[0] < data.intersections[0].distance)
			|| (data.intersections[0].distance < 0))
		&& ((data.distance[0] < data.intersections[1].distance)
			|| (data.intersections[1].distance < 0)))
		return (get_intesection_from_distance(data.distance[0], data.origin,
				data.ray_direction, data.cylinder));
	return (intersect_ray_cylinder_helper_internal(data));
}

#pragma clang diagnostic pop
