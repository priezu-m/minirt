/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: vector_functions.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/20 00:13:37                                            */
/*   Updated:  2023/10/26 07:58:15                                            */
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

bool	is_normal_vector3(t_vector3 v)
{
	const long double	magnitude = get_magnitude_vector3(v);

	if ((magnitude < 1.l - 1e-16l)
		|| (magnitude > 1.l + 1e-16l))
		return (false);
	return (true);
}

t_vector3	cross_product_vector3(t_vector3 v1, t_vector3 v2)
{
	return ((t_vector3){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x});
}

long double	get_magnitude_vector3(t_vector3 v1)
{
	return (sqrtl(powl(v1.x, 2) + powl(v1.y, 2) + powl(v1.z, 2)));
}

t_vector3	normalize_vector3(t_vector3 v1)
{
	const long double	lenght = get_magnitude_vector3(v1);

	if (lenght < 1.E-14L && lenght > -1.E-14L)
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

#pragma clang diagnostic pop
