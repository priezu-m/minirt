/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: direct_light.c                                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/11/12 19:27:07                                            */
/*   Updated:  2023/11/15 02:00:14                                            */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "../intersections/intersections.h"
#include <stdbool.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static bool	check_plane_intersection(t_parameters parameters,
				t_vector ray_direction, int ignored, t_shape_type shape_type)
{
	int					i;
	long double			t;
	const long double	max_t = get_magnitude(
			substract(parameters.camera.position, parameters.light.position));

	i = 0;
	while (i < parameters.plane_list.size)
	{
		if (i != ignored || shape_type != e_plane)
		{
			t = intersect_ray_plane(ray_direction, parameters.camera.position,
					parameters.plane_list.planes[i]).distance;
			if (t >= 0 && t < max_t)
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_sphere_intersection(t_parameters parameters,
				t_vector ray_direction, int ingnore, t_shape_type shape_type)
{
	int					i;
	long double			t;
	t_intersection		intersection;
	const long double	max_t = get_magnitude(
			substract(parameters.camera.position, parameters.light.position));

	i = 0;
	while (i < parameters.sphere_list.size)
	{
		if (i != ingnore || shape_type != e_sphere)
		{
			intersection = intersect_ray_sphere(ray_direction,
					parameters.camera.position,
					parameters.sphere_list.spheres[i]);
			t = intersection.distance;
			if (t >= 0 && t < max_t)
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_cylinder_intersection(t_parameters parameters,
				t_vector ray_direction, int ingnore, t_shape_type shape_type)
{
	int					i;
	long double			t;
	const long double	max_t = get_magnitude(
			substract(parameters.camera.position, parameters.light.position));

	i = 0;
	while (i < parameters.cylinder_list.size)
	{
		if (i != ingnore || shape_type != e_cylinder)
		{
			t = intersect_ray_cylinder(ray_direction,
					parameters.camera.position,
					parameters.cylinder_list.cylinders[i]).distance;
			if (t >= 0 && t < max_t)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	direct_light(t_shape_type shape_type, int i,
			t_vector intersection_point, t_parameters parameters)
{
	bool		ret;
	t_vector	ray_direction;

	if (parameters.light.initialized == false)
		return (false);
	parameters.camera.position = intersection_point;
	ray_direction = normalize(substract(parameters.light.position,
				intersection_point));
	ret = check_plane_intersection(parameters, ray_direction, i, shape_type);
	if (ret == false)
		return (false);
	ret = check_sphere_intersection(parameters, ray_direction, i, shape_type);
	if (ret == false)
		return (false);
	ret = check_cylinder_intersection(parameters, ray_direction, i, shape_type);
	if (ret == false)
		return (false);
	return (ret);
}

#pragma clang diagnostic pop
