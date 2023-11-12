/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersect_ray_cylinder.c                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 16:43:27                                            */
/*   Updated:  2023/11/12 12:59:47                                            */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"
#include <math.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static long double	check_intersection_whit_lid(t_vector ray_direction,
						t_vector origin, t_cylinder cylinder)
{
	const t_vector	lid_center1 = add(cylinder.geometric_center,
			multiply(cylinder.direction, -cylinder.height / 2.0L));
	const t_vector	lid_center2 = add(cylinder.geometric_center,
			multiply(cylinder.direction, cylinder.height / 2.0L));
	long double		t1;
	long double		t2;

	t1 = intersect_ray_plane(ray_direction, origin,
			(t_plane){.normal = cylinder.direction, .position = lid_center1});
	t2 = intersect_ray_plane(ray_direction, origin,
			(t_plane){.normal = cylinder.direction, .position = lid_center2});
	if (get_magnitude(
			substract(lid_center1, add(origin, multiply(ray_direction, t1))))
		> (cylinder.diameter / 2))
		t1 = -1;
	if (get_magnitude(
			substract(lid_center2, add(origin, multiply(ray_direction, t2))))
		> (cylinder.diameter / 2))
		t2 = -1;
	if (t2 < 0)
		return (t1);
	return (t2);
}

typedef struct s_discriminant
{
	long double	a;
	long double	b;
	long double	c;
	long double	bb_4ac;

}t_discriminant;

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

long double	intersect_ray_cylinder(t_vector ray_direction, t_vector origin,
				t_cylinder cylinder)
{
	const t_vector			lid_center = add(cylinder.geometric_center,
			multiply(cylinder.direction, -cylinder.height / 2.0L));
	const t_discriminant	discriminant = get_discriminant(ray_direction,
			cylinder, origin, lid_center);
	long double				t1;
	long double				t2;
	long double				m;

	if (discriminant.bb_4ac < 0.L)
		return (-1);
	t1 = (-discriminant.b
			- sqrtl(discriminant.bb_4ac)) / (2.0L * discriminant.a);
	m = dot_product(ray_direction, cylinder.direction) * t1;
	m += dot_product(substract(origin, lid_center), cylinder.direction);
	if (m > cylinder.height || m < 0 || isnan(m) == true)
		t1 = check_intersection_whit_lid(ray_direction, origin, cylinder);
	t2 = (-discriminant.b + sqrtl(discriminant.bb_4ac))
		/ (2.0L * discriminant.a);
	m = dot_product(ray_direction, cylinder.direction) * t2;
	m += dot_product(substract(origin, lid_center), cylinder.direction);
	if (m > cylinder.height || m < 0 || isnan(m) == true)
		t2 = check_intersection_whit_lid(ray_direction, origin, cylinder);
	if (((t1 < t2) || (t2 < 0)) && t1 >= 0)
		return (t1);
	return (t2);
}

#pragma clang diagnostic pop
