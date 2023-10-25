/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: vector_functions.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/20 00:13:37                                            */
/*   Updated:  2023/10/25 18:25:07                                            */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdbool.h>
#include <math.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

bool	is_normal_vector3(t_vector3 vector)
{
	const long double	magnitude = sqrtl(vector.x * vector.x
			+ vector.y * vector.y + vector.z * vector.z);

	if ((magnitude < 1.l - 1e-16l)
		|| (magnitude > 1.l + 1e-16l))
		return (false);
	return (true);
}

t_vector3	cross_product_vector3(t_vector3 v1, t_vector3 v2)
{
		return ((t_vector3)
		{
				v1.y * v2.z - v1.z * v2.y,
				v1.z * v2.x - v1.x * v2.z,
				v1.x * v2.y - v1.y * v2.x
		});
}

long double	get_magnitude_vector3(t_vector3 v1)
{
	return (sqrtl(powl(v1.x, 2) + powl(v1.y, 2) + powl(v1.z, 2)));
}

t_vector3	normalize_vector3(t_vector3 v1)
{
	const long double	lenght = get_magnitude_vector3(v1);

	if (lenght < 1.E-14L &&  lenght > -1.E-14L)
		return ((t_vector3){0});
	v1.x /= lenght;
	v1.y /= lenght;
	v1.z /= lenght;
	return (v1);
}

long double	dot_product_vector3(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vector3_substract(t_vector3 v1, t_vector3 v2)
{
	return ((t_vector3) {.x = v1.x - v2.x, .y = v1.y - v2.y, .z = v1.z - v2.z});
}

t_vector3	vector3_multiply(t_vector3 v1, long double s)
{
	return ((t_vector3) {.x = v1.x * 2, .y = v1.y * s, .z = v1.z * s});
}

t_vector3	vector3_add(t_vector3 v1, t_vector3 v2)
{
	return ((t_vector3) {.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z});
}

/*
bool		is_normal_vector2(t_vector2 vector)
{
	const long double	magnitude = sqrtl(vector.x * vector.x
			+ vector.y * vector.y);

	if ((magnitude < 1.l - 1e-16l)
		|| (magnitude > 1.l + 1e-16l))
		return (false);
	return (true);
}

t_vector2	normalize_vector2(t_vector2 v1)
{
	const long double	lenght = get_magnitude_vector2(v1);

	v1.x /= lenght;
	v1.y /= lenght;
	return (v1);
}

long double	get_magnitude_vector2(t_vector2 v1)
{
	return (sqrtl(powl(v1.x, 2) + powl(v1.y, 2)));
}

long double	dot_product_vector2(t_vector2 v1, t_vector2 v2)
{
	 return (v1.x * v2.x + v1.y * v2.y);
}

long double	get_angle_vector2(t_vector2 v1, t_vector2 v2)
{
	return (acosl(
			(dot_product_vector2(v1, v2))
			/ (get_magnitude_vector2(v1) * get_magnitude_vector2(v2))));
}
*/

#pragma clang diagnostic pop
