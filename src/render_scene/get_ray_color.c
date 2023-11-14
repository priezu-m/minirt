/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_ray_color.c                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 08:50:14                                            */
/*   Updated:  2023/11/14 23:29:41                                            */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "../intersections/intersections.h"
#include <math.h>
#include <stdbool.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

unsigned int	get_ray_color(t_vector ray_direction, t_parameters parameters)
{
	t_color		color;
	long double	min_t;

	color = (t_color){.r = 0, .g = 0, .b = 0};
	if (parameters.ambient_lighting.initialized == true)
		color = color_multiply(parameters.ambient_lighting.color,
				parameters.ambient_lighting.intensity);
	min_t = HUGE_VALL;
	color = check_plane_intersection_color(parameters, ray_direction, &min_t,
			color);
	color = check_sphere_intersection_color(parameters, ray_direction, &min_t,
			color);
	color = check_cylinder_intersection_color(parameters, ray_direction, &min_t,
			color);
	return (*(unsigned *)&color);
}

#pragma clang diagnostic pop
