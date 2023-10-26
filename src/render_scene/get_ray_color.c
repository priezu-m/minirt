/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_ray_color.c                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 08:50:14                                            */
/*   Updated:  2023/10/26 09:43:05                                            */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include "../intersections/intersections.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

unsigned int	get_ray_color(t_vector3 ray_direction, t_parameters parameters)
{
	t_color		color;
	long double	t;

	color = (t_color){.r = 0, .g = 0, .b = 0};
	if (parameters.ambient_lighting.is_initialized == true)
		color = parameters.ambient_lighting.color;
	if (parameters.sphere_list.size > 0)
	{
		t = intersect_ray_sphere(ray_direction, parameters.camera.position,
			parameters.sphere_list.sphere_list[0]);
		if (t > 0)
			color = parameters.sphere_list.sphere_list[0].color;
	}
	return (*(unsigned *)&color);
}

#pragma clang diagnostic pop
