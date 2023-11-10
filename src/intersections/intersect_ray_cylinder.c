/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_cylinder.c                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 16:43:27                                            */
/*   Updated:  2023/11/10 17:05:43                                            */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

#include <math.h>

static long double	check_intersection_whit_lid(t_vector3 ray_direction, t_vector3 origin, t_cylinder cylinder)
{
	const t_vector3	lid_center1 = vector3_add(cylinder.position,
			vector3_multiply(cylinder.orientation_vector, -cylinder.height / 2.0L));
	const t_vector3	lid_center2 = vector3_add(cylinder.position,
			vector3_multiply(cylinder.orientation_vector, cylinder.height / 2.0L));
	long double	t1 = intersect_ray_plane(ray_direction, origin,
			(t_plane){.orientation_vector = cylinder.orientation_vector, .position = lid_center1});
	long double	t2 = intersect_ray_plane(ray_direction, origin,
			(t_plane){.orientation_vector = cylinder.orientation_vector, .position = lid_center2});

	if (get_magnitude_vector3(
		vector3_substract(lid_center1, vector3_add(origin, vector3_multiply(ray_direction , t1))))
		> (cylinder.diameter / 2))
		t1 = - 1;
	if (get_magnitude_vector3(
		vector3_substract(lid_center2, vector3_add(origin, vector3_multiply(ray_direction , t2))))
		> (cylinder.diameter / 2))
		t2 = - 1;
	if (t2 < 0)
		return (t1);
	return (t2);
}

long double	intersect_ray_cylinder(t_vector3 ray_direction, t_vector3 origin, t_cylinder cylinder)
{
	const t_vector3	lid_center = vector3_add(cylinder.position,
			vector3_multiply(cylinder.orientation_vector, -cylinder.height / 2.0L));
	long double		a;
	long double		b;
	long double		c;
	long double		t1;
	long double		t2;
	long double		m;

	a = dot_product_vector3(ray_direction, ray_direction);
	a -= powl(dot_product_vector3(ray_direction, cylinder.orientation_vector), 2);
	b = dot_product_vector3(ray_direction, vector3_substract(origin, lid_center));
	b -= dot_product_vector3(ray_direction, cylinder.orientation_vector)
		* dot_product_vector3(vector3_substract(origin, lid_center), cylinder.orientation_vector);
	b *= 2;
	c = dot_product_vector3(vector3_substract(origin, lid_center), vector3_substract(origin, lid_center));
	c -= powl(dot_product_vector3(vector3_substract(origin, lid_center), cylinder.orientation_vector), 2);
	c -= powl(cylinder.diameter / 2, 2);
	if ((b * b - 4 * c * a) < 0.L) 
		return (-1);
	t1 = (-b - sqrtl(b * b - 4 * c * a)) / (2.0L * a);
	m = dot_product_vector3(ray_direction, cylinder.orientation_vector) * t1;
	m += dot_product_vector3(vector3_substract(origin, lid_center), cylinder.orientation_vector);
	if (m > cylinder.height || m < 0)// || isnan(m) == true)
		t1 = check_intersection_whit_lid(ray_direction, origin, cylinder);
//		t1 = -1;
	t2 = (-b + sqrtl(b * b - 4 * c * a)) / (2.0L * a);
	m = dot_product_vector3(ray_direction, cylinder.orientation_vector) * t2;
	m += dot_product_vector3(vector3_substract(origin, lid_center), cylinder.orientation_vector);
	if (m > cylinder.height || m < 0)// || isnan(m) == true)
		t2 = check_intersection_whit_lid(ray_direction, origin, cylinder);
//		t2 = -1;
	if (((t1 < t2) || (t2 < 0)) && t1 >= 0)
		return (t1);
	if (isnan(t2) == false)
		return (t2);
	return (-1);
}

#pragma clang diagnostic pop
