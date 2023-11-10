/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_ray_color.c                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 08:50:14                                            */
/*   Updated:  2023/11/10 18:59:48                                            */
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

unsigned int	get_ray_color(t_vector ray_direction, t_parameters parameters)
{
	t_color		color;
	long double min_t;
	long double	t;
	int			i;

	color = (t_color){.r = 0, .g = 0, .b = 0};
	if (parameters.ambient_lighting.initialized == true)
		color = parameters.ambient_lighting.color;
	min_t = HUGE_VALL;
	i = 0;
	while (i < parameters.plane_list.size)
	{
		t = intersect_ray_plane(ray_direction, parameters.camera.position, parameters.plane_list.planes[i]);
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
	i = 0;
	while (i < parameters.sphere_list.size)
	{
		t = intersect_ray_sphere(ray_direction, parameters.camera.position, parameters.sphere_list.spheres[i]);
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
	i = 0;
	while (i < parameters.cylinder_list.size)
	{
		t = intersect_ray_cylinder(ray_direction, parameters.camera.position, parameters.cylinder_list.cylinder_list[i]);
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
	return (*(unsigned *)&color);
}

#pragma clang diagnostic pop
