/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_ray_color.c                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 08:50:14                                            */
/*   Updated:  2023/11/14 17:54:43                                            */
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

static t_color	check_plane_intersection(t_parameters parameters,
					t_vector ray_direction, long double *min_t, t_color color)
{
	int				i;
	long double		t;
	long double		s;
	t_intersection	intersection;
	t_vector		direction_to_light;

	i = 0;
	while (i < parameters.plane_list.size)
	{
		intersection = intersect_ray_plane(ray_direction, parameters.camera.position,
				parameters.plane_list.planes[i]);
		t = intersection.distance;
		if (t >= 0)
		{
			if (t < *min_t)
			{
				*min_t = t;
				color = (t_color){0};
				if (direct_light(e_plane, i, intersection.point, parameters) == true)
				{
					direction_to_light = normalize(substract(parameters.light.position, intersection.point));
					s = fabsl(dot_product(direction_to_light, intersection.surface_normal));
					if (s > 0)
						color = color_absorb(parameters.plane_list.planes[i].color,
								color_multiply(color_multiply(parameters.light.color, parameters.light.brightness),
									s));
				}
				if (parameters.ambient_lighting.initialized == true)
					color = color_add(color, color_absorb(parameters.plane_list.planes[i].color,
								color_multiply(parameters.ambient_lighting.color,
									parameters.ambient_lighting.intensity)));
			}
		}
		i++;
	}
	return (color);
}

static t_color	check_sphere_intersection(t_parameters parameters,
					t_vector ray_direction, long double *min_t, t_color color)
{
	int				i;
	long double		t;
	long double		s;
	t_intersection	intersection;
	t_vector		direction_to_light;

	i = 0;
	while (i < parameters.sphere_list.size)
	{
		intersection = intersect_ray_sphere(ray_direction, parameters.camera.position,
				parameters.sphere_list.spheres[i]);
		t = intersection.distance;
		if ((t >= 0) && (t < *min_t))
		{
				*min_t = t;
				color = (t_color){0};
				if (direct_light(e_sphere, i, intersection.point, parameters) == true)
				{
					direction_to_light = normalize(substract(parameters.light.position, intersection.point));
					s = dot_product(direction_to_light, intersection.surface_normal);
					if (s > 0)
						color = color_absorb(parameters.sphere_list.spheres[i].color,
								color_multiply(color_multiply(parameters.light.color, parameters.light.brightness),
									s));
				}
				if (parameters.ambient_lighting.initialized == true)
					color = color_add(color, color_absorb(parameters.sphere_list.spheres[i].color,
								color_multiply(parameters.ambient_lighting.color,
									parameters.ambient_lighting.intensity)));
		}
		i++;
	}
	return (color);
}

static t_color	check_cylinder_intersection(t_parameters parameters,
					t_vector ray_direction, long double *min_t, t_color color)
{
	int				i;
	long double		t;
	long double		s;
	t_intersection	intersection;
	t_vector		direction_to_light;

	i = 0;
	while (i < parameters.cylinder_list.size)
	{
		intersection = intersect_ray_cylinder(ray_direction, parameters.camera.position,
				parameters.cylinder_list.cylinder_list[i]);
		t = intersection.distance;
		if (t >= 0)
		{
			if (t < *min_t)
			{
				*min_t = t;
				color = (t_color){0};
				if (direct_light(e_cylinder, i, intersection.point, parameters) == true)
				{
					direction_to_light = normalize(substract(parameters.light.position, intersection.point));
					s = dot_product(direction_to_light, intersection.surface_normal);
					if (s > 0)
						color = color_absorb(parameters.cylinder_list.cylinder_list[i].color,
								color_multiply(color_multiply(parameters.light.color, parameters.light.brightness),
									s));
				}
				if (parameters.ambient_lighting.initialized == true)
					color = color_add(color, color_absorb(parameters.cylinder_list.cylinder_list[i].color,
								color_multiply(parameters.ambient_lighting.color,
									parameters.ambient_lighting.intensity)));
			}
		}
		i++;
	}
	return (color);
}

unsigned int	get_ray_color(t_vector ray_direction, t_parameters parameters)
{
	t_color		color;
	long double	min_t;

	color = (t_color){.r = 0, .g = 0, .b = 0};
	if (parameters.ambient_lighting.initialized == true)
		color = color_multiply(parameters.ambient_lighting.color,
					parameters.ambient_lighting.intensity);
	min_t = HUGE_VALL;
	color = check_plane_intersection(parameters, ray_direction, &min_t, color);
	color = check_sphere_intersection(parameters, ray_direction, &min_t, color);
	color = check_cylinder_intersection(parameters, ray_direction, &min_t,
			color);
	return (*(unsigned *)&color);
}

#pragma clang diagnostic pop
