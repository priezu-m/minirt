/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: check_plane_intersection_color.c                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/11/14 23:24:00                                            */
/*   Updated:  2023/11/14 23:27:19                                            */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "../intersections/intersections.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static t_color	get_color(int i, t_intersection intersection,
					t_parameters parameters)
{
	long double	s;
	t_vector	direction_to_light;
	t_color		color;

	color = (t_color){0};
	if (direct_light(e_plane, i, intersection.point, parameters)
		== true)
	{
		direction_to_light = normalize(substract(
					parameters.light.position, intersection.point));
		s = fabsl(dot_product(direction_to_light,
					intersection.surface_normal));
		color = color_absorb(
				parameters.plane_list.planes[i].color,
				color_multiply(color_multiply(
						parameters.light.color,
						parameters.light.brightness), s));
	}
	if (parameters.ambient_lighting.initialized == true)
		color = color_add(color, color_absorb(
					parameters.plane_list.planes[i].color,
					color_multiply(
						parameters.ambient_lighting.color,
						parameters.ambient_lighting.intensity)));
	return (color);
}

t_color	check_plane_intersection_color(t_parameters parameters,
					t_vector ray_direction, long double *min_t, t_color color)
{
	int				i;
	long double		t;
	t_intersection	intersection;

	i = 0;
	while (i < parameters.plane_list.size)
	{
		intersection = intersect_ray_plane(ray_direction,
				parameters.camera.position, parameters.plane_list.planes[i]);
		t = intersection.distance;
		if (t >= 0)
		{
			if (t < *min_t)
			{
				*min_t = t;
				color = get_color(i, intersection, parameters);
			}
		}
		i++;
	}
	return (color);
}

#pragma clang diagnostic pop
