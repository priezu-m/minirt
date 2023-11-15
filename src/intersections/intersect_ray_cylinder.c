/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_cylinder.c                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 16:43:27                                            */
/*   Updated:  2023/11/15 01:50:12                                            */
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

static t_intersection	check_intersection_whit_lid_helper(long double t2,
		t_vector ray_direction, t_vector origin, t_cylinder cylinder)
{
	if (t2 >= 0)
		return ((t_intersection){.distance = t2, .point = add(origin,
				multiply(ray_direction, t2)),
			.surface_normal = multiply(cylinder.direction, 1)});
	return ((t_intersection){.distance = -1});
}

t_intersection	check_intersection_whit_lid(t_vector ray_direction,
							t_vector origin, t_cylinder cylinder)
{
	const t_vector	lid_center1 = add(cylinder.geometric_center,
			multiply(cylinder.direction, -cylinder.height / 2.0L));
	const t_vector	lid_center2 = add(cylinder.geometric_center,
			multiply(cylinder.direction, cylinder.height / 2.0L));
	long double		t1;
	long double		t2;

	t1 = intersect_ray_plane(ray_direction, origin, (t_plane){.normal
			= cylinder.direction, .position = lid_center1}).distance;
	t2 = intersect_ray_plane(ray_direction, origin, (t_plane){.normal
			= cylinder.direction, .position = lid_center2}).distance;
	if (get_magnitude(
			substract(lid_center1, add(origin, multiply(ray_direction, t1))))
		> (cylinder.diameter / 2))
		t1 = -1;
	if (get_magnitude(
			substract(lid_center2, add(origin, multiply(ray_direction, t2))))
		> (cylinder.diameter / 2))
		t2 = -1;
	if (t1 >= 0 && ((t1 < t2) || (t2 < 0)))
		return ((t_intersection){.distance = t1, .point = add(origin,
				multiply(ray_direction, t1)),
			.surface_normal = multiply(cylinder.direction, -1)});
	return (check_intersection_whit_lid_helper(t2, ray_direction, origin,
			cylinder));
}

static t_discriminant	get_discriminant(t_vector ray_direction,
							t_cylinder cylinder, t_vector origin,
							t_vector lid_center)
{
	long double		a;
	long double		b;
	long double		c;

	a = dot_product(ray_direction, ray_direction);
	a -= powl(dot_product(ray_direction, cylinder.direction), 2);
	b = dot_product(ray_direction, substract(origin, lid_center));
	b -= dot_product(ray_direction, cylinder.direction)
		* dot_product(substract(origin, lid_center), cylinder.direction);
	b *= 2;
	c = dot_product(substract(origin, lid_center),
			substract(origin, lid_center));
	c -= powl(dot_product(substract(origin, lid_center), cylinder.direction),
			2);
	c -= powl(cylinder.diameter / 2, 2);
	return ((t_discriminant){.a = a, .b = b, .c = c,
		.bb_4ac = b * b - 4 * a * c});
}

t_intersection	intersect_ray_cylinder(t_vector ray_direction, t_vector origin,
				t_cylinder cylinder)
{
	const t_vector			lid_center = add(cylinder.geometric_center,
			multiply(cylinder.direction, -cylinder.height / 2.0L));
	const t_discriminant	discriminant = get_discriminant(ray_direction,
			cylinder, origin, lid_center);
	long double				distance[2];
	t_intersection			intersections[2];
	long double				m;

	intersections[0].distance = -1;
	intersections[1].distance = -1;
	if (discriminant.bb_4ac < 0.L)
		return ((t_intersection){.distance = -1});
	distance[0] = (-discriminant.b
			- sqrtl(discriminant.bb_4ac)) / (2.0L * discriminant.a);
	m = dot_product(ray_direction, cylinder.direction) * distance[0];
	m += dot_product(substract(origin, lid_center), cylinder.direction);
	if (m > cylinder.height || m < 0 || isnan(m) == true)
	{
		distance[0] = -1;
		intersections[0] = check_intersection_whit_lid(ray_direction, origin,
				cylinder);
	}
	return (intersect_ray_cylinder_helper((t_intersect_ray_cylinder_data)
			{distance, origin, cylinder, intersections, ray_direction,
				discriminant, lid_center, m}));
}

#pragma clang diagnostic pop
