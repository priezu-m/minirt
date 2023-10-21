/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: vector_functions.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/20 00:13:37                                            */
/*   Updated:  2023/10/20 06:17:17                                            */
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

bool	is_normal(t_vector vector)
{
	const long double	magnitude = sqrtl(vector.x * vector.x
			+ vector.y * vector.y + vector.z * vector.z);

	if ((magnitude < 1.L - 1E-16L)
		|| (magnitude > 1.L + 1E-16L))
		return (false);
	return (true);
}

#pragma clang diagnostic pop
