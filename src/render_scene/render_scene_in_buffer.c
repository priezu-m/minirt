/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: render_scene_in_buffer.c                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/23 08:56:27                                            */
/*   Updated:  2023/10/26 08:49:59                                            */
/*                                                                            */
/* ************************************************************************** */

#include "render_scene.h"
#include <math.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

#define PIL 3.141592653589793238462643383279502884L

typedef struct s_camera_data
{
	long double	ratio;
	long double	width_tan;
	long double	height_tan;
	t_vector3	right;
	t_vector3	up;
	t_vector3	orientation;
	t_vector3	origin;
}t_camera_data;

static t_vector3	get_ray_direction(t_camera_data camera_data, long double w,
			long double h)
{
	t_vector3	direction;
	t_vector3	aux;

	direction = camera_data.origin;
	aux = vector3_add(direction, camera_data.orientation);
	direction = aux;
	aux = vector3_add(direction,
			vector3_multiply(camera_data.right, camera_data.width_tan * w));
	direction = aux;
	aux = vector3_add(direction,
			vector3_multiply(camera_data.up, camera_data.height_tan * h));
	direction = aux;
	return (normalize_vector3(direction));
}

static long double	normalize_point(long double current, long double max)
{
	return (((current * 2) / max) - 1);
}

static t_vector3	get_up_vector(t_camera_data camera_data)
{
	long double		radians;
	const t_vector3	reference_vector = normalize_vector3((t_vector3)
		{.x = camera_data.orientation.x, .z = camera_data.orientation.z});
	const t_vector3	p = vector3_multiply(camera_data.orientation,
			dot_product_vector3(camera_data.orientation, reference_vector));
	const t_vector3	o = vector3_substract(reference_vector, p);

	if (get_magnitude_vector3(reference_vector) < 1.E-14L
		&& get_magnitude_vector3(reference_vector) > -1.E-14L)
	{
		if (camera_data.orientation.y > 0)
			return ((t_vector3){.x = 0, .y = 0, .z = 1});
		return ((t_vector3){.x = 0, .y = 0, .z = -1});
	}
	radians = 90.L * PIL / 180.L;
	if ((camera_data.orientation.x >= 0 && camera_data.orientation.y >= 0)
		|| (camera_data.orientation.x < 0
			&& camera_data.orientation.y >= 0))
		radians = -radians;
	if (camera_data.orientation.y < 1.E-14L
		&& camera_data.orientation.y > -1.E-14L)
		return ((t_vector3){.x = 0, .y = 1, .z = 0});
	return (normalize_vector3(vector3_add(
				vector3_multiply(camera_data.orientation, cosl(radians)),
				vector3_multiply(o, sinl(radians)))));
}

static t_camera_data	get_camera_data(t_parameters parameters, int height,
							int width)
{
	t_camera_data	camera_data;

	camera_data.origin = parameters.camera.position;
	camera_data.orientation = parameters.camera.orientation_vector;
	camera_data.ratio = ((long double)height / (long double)width);
	camera_data.width_tan = tanl(((parameters.camera.field_of_view / 2) * PIL)
			/ 180);
	camera_data.height_tan = camera_data.width_tan * camera_data.ratio;
	camera_data.up = get_up_vector(camera_data);
	camera_data.right = cross_product_vector3(camera_data.up,
			camera_data.orientation);
	return (camera_data);
}

void	render_scene_in_buffer(t_parameters parameters, unsigned int *buffer,
			int height, int width)
{
	const int		width_copy = width;
	const int		height_copy = height;
	t_vector3		ray_direction;
	t_camera_data	camera_data;

	camera_data = get_camera_data(parameters, height, width);
	while (height > 0)
	{
		width = 0;
		while (width < width_copy)
		{
			ray_direction = get_ray_direction(camera_data,
					normalize_point(width, width_copy),
					normalize_point(height, height_copy));
			buffer[((height_copy - height) * width_copy) + width]
				= get_ray_color(ray_direction, parameters);
			width++;
		}
		height--;
	}
}

#pragma clang diagnostic pop
