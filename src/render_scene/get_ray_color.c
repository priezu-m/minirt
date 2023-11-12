/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_ray_color.c                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 08:50:14                                            */
/*   Updated:  2023/11/12 13:22:42                                            */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "../intersections/intersections.h"
#include <math.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static t_color	check_plane_intersection(t_parameters parameters,
					t_vector ray_direction, long double min_t, t_color color)
{
	int			i;
	long double	t;

	i = 0;
	while (i < parameters.plane_list.size)
	{
		t = intersect_ray_plane(ray_direction, parameters.camera.position,
				parameters.plane_list.planes[i]);
		if (t >= 0)
		{
			if (t < min_t)
			{
				min_t = t;
				color = parameters.plane_list.planes[i].color;
			}
		}
		i++;
	}
	return (color);
}

static t_color	check_sphere_intersection(t_parameters parameters,
					t_vector ray_direction, long double min_t, t_color color)
{
	int			i;
	long double	t;

	i = 0;
	while (i < parameters.sphere_list.size)
	{
		t = intersect_ray_sphere(ray_direction, parameters.camera.position,
				parameters.sphere_list.spheres[i]);
		if (t >= 0)
		{
			if (t < min_t)
			{
				min_t = t;
				color = parameters.sphere_list.spheres[i].color;
			}
		}
		i++;
	}
	return (color);
}

static t_color	check_cylinder_intersection(t_parameters parameters,
					t_vector ray_direction, long double min_t, t_color color)
{
	int			i;
	long double	t;

	i = 0;
	while (i < parameters.cylinder_list.size)
	{
		t = intersect_ray_cylinder(ray_direction, parameters.camera.position,
				parameters.cylinder_list.cylinder_list[i]);
		if (t >= 0)
		{
			if (t < min_t)
			{
				min_t = t;
				color = parameters.cylinder_list.cylinder_list[i].color;
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
		color = parameters.ambient_lighting.color;
	min_t = HUGE_VALL;
	color = check_plane_intersection(parameters, ray_direction, min_t, color);
	color = check_sphere_intersection(parameters, ray_direction, min_t, color);
	color = check_cylinder_intersection(parameters, ray_direction, min_t,
			color);
	return (*(unsigned *)&color);
}

#pragma clang diagnostic pop
