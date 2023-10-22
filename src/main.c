/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.c                                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/25 17:27:48                                            */
/*   Updated:  2023/10/22 09:42:36                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters/parameters.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <mlx.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

#define  WIDTH 1080
#define  HEIGHT 720

static void	stablish_conection(void **connection_id, void **window_id,
		void **img_id)
{
	*connection_id = mlx_init();
	if (connection_id == NULL)
	{
		perror("Error\nFailed to stablish a connection with the X server");
		return ;
	}
	*window_id = mlx_new_window(*connection_id , WIDTH, HEIGHT, "Minirt");
	if (*window_id == NULL)
	{
		perror("Error\nFailed to create a window");
		mlx_destroy_display(*connection_id);
		return ;
	}
	*img_id = mlx_new_image(*connection_id, WIDTH, HEIGHT);
	if (*img_id == NULL)
	{
		perror("Error\nFailed to create a buffer");
		mlx_destroy_window(*connection_id, *window_id);
		mlx_destroy_display(*connection_id);
		return ;
	}
}

typedef struct	s_data
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

static void	render_scene(t_parameters parameters)
{
	void		*connection_id;
	void		*window_id;
	void		*img_id;
	t_data		img_data;
	const char	msg[] = "This system not supported, aborting\n";

	stablish_conection(&connection_id, &window_id, &img_id);
	if (connection_id == NULL || window_id == NULL || img_id == NULL)
		return ;
	img_data.addr = mlx_get_data_addr(img_id, &img_data.bits_per_pixel,
		&img_data.line_length, &img_data.endian);	
	if (img_data.bits_per_pixel == 32 && img_data.endian == 0)
	{
		//visibility_notify (12) (0) (put image again)
		//keypress_notify (02) (0) (check esc close close programm if pressed)
		//DestroyNotify(17) (0) (close_programm)
		//render_scene_in_buffer(parameters, img_data.addr, HEIGHT, WIDTH);
		mlx_put_image_to_window(connection_id, window_id, img_id, 0, 0);
		while (1);
	}
	else
		write(STDERR_FILENO, msg, sizeof(msg));
	mlx_destroy_image(connection_id, img_id);
	mlx_destroy_window(connection_id, window_id);
	mlx_destroy_display(connection_id);
}

int	main(int argc, char **argv)
{
	t_parameters	parameters;

	if (argc != 2)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	parameters = get_parameters(argv[1]);
	if (parameters.parameters_valid == false)
	{
		destroy_parameters(parameters);
		return (EXIT_FAILURE);
	}
	render_scene(parameters);
	destroy_parameters(parameters);
	return (EXIT_SUCCESS);
}

/*static void	print_parameters(t_parameters parameters)
{
	int	i;

	if (parameters.ambient_lighting.is_initialized == true)
	{
		printf("Ambien lighting: {intensity: %.3Lf, color: %d,%d,%d}\n",
			parameters.ambient_lighting.ambient_lighting_intensity,
			parameters.ambient_lighting.color.r,
			parameters.ambient_lighting.color.g,
			parameters.ambient_lighting.color.b);
	}
	printf("Camera:\n{position: (%.3Lf,%.3Lf,%.3Lf), orientation: "
		"%LF,%.3Lf,%.3Lf, field of view: %.3Lf}\n",
		parameters.camera.position.x,
		parameters.camera.position.y,
		parameters.camera.position.z,
		parameters.camera.orientation_vector.x,
		parameters.camera.orientation_vector.y,
		parameters.camera.orientation_vector.z,
		parameters.camera.field_of_view);
	if (parameters.light.is_initialized == true)
	{
		printf("Light: {position: (%.3Lf,%.3Lf,%.3Lf), intensity: %.3Lf,"
				" color: %d,%d,%d}\n",
				parameters.light.position.x,
				parameters.light.position.y,
				parameters.light.position.z,
				parameters.light.brightness,
				parameters.light.color.r,
				parameters.light.color.g,
				parameters.light.color.b);
	}
	if (parameters.cylinder_list.size != 0)
	{
		i = 0;
		printf("Cylinder list: {size: %d\n", parameters.cylinder_list.size);
		while (parameters.cylinder_list.size > 0)
		{
			printf("\t[%d]{position: (%.1Lf,%.1Lf,%.1Lf), direction: "
				"(%.1Lf,%.1Lf,%.1Lf), diameter: %.1Lf,"
				" height: %.1Lf, color: %d,%d,%d}\n", i,
				parameters.cylinder_list.cylinder_list[i].position.x,
				parameters.cylinder_list.cylinder_list[i].position.y,
				parameters.cylinder_list.cylinder_list[i].position.z,
				parameters.cylinder_list.cylinder_list[i].orientation_vector.x,
				parameters.cylinder_list.cylinder_list[i].orientation_vector.y,
				parameters.cylinder_list.cylinder_list[i].orientation_vector.z,
				parameters.cylinder_list.cylinder_list[i].diameter,
				parameters.cylinder_list.cylinder_list[i].height,
				parameters.cylinder_list.cylinder_list[i].color.r,
				parameters.cylinder_list.cylinder_list[i].color.g,
				parameters.cylinder_list.cylinder_list[i].color.b);
			i++;
			parameters.cylinder_list.size--;
		}
	}
	if (parameters.plane_list.size != 0)
	{
		i = 0;
		printf("Plane list: {size: %d\n", parameters.plane_list.size);
		while (parameters.plane_list.size > 0)
		{
			printf("\t[%d]{position: (%.3Lf,%.3Lf,%.3Lf), normal:"
				" (%.3Lf,%.3Lf,%.3Lf), color: %d,%d,%d}\n", i,
				parameters.plane_list.plane_list[i].position.x,
				parameters.plane_list.plane_list[i].position.y,
				parameters.plane_list.plane_list[i].position.z,
				parameters.plane_list.plane_list[i].orientation_vector.x,
				parameters.plane_list.plane_list[i].orientation_vector.y,
				parameters.plane_list.plane_list[i].orientation_vector.z,
				parameters.plane_list.plane_list[i].color.r,
				parameters.plane_list.plane_list[i].color.g,
				parameters.plane_list.plane_list[i].color.b);
			i++;
			parameters.plane_list.size--;
		}
	}
	if (parameters.sphere_list.size != 0)
	{
		i = 0;
		printf("Sphere list: {size: %d\n", parameters.sphere_list.size);
		while (parameters.sphere_list.size > 0)
		{
			printf("\t[%d]{position: (%.3Lf,%.3Lf,%.3Lf), diameter: "
					"%.3Lf, color: %d,%d,%d}\n", i,
					parameters.sphere_list.sphere_list[i].position.x,
					parameters.sphere_list.sphere_list[i].position.y,
					parameters.sphere_list.sphere_list[i].position.z,
					parameters.sphere_list.sphere_list[i].diameter,
					parameters.sphere_list.sphere_list[i].color.r,
					parameters.sphere_list.sphere_list[i].color.g,
					parameters.sphere_list.sphere_list[i].color.b);
			i++;
			parameters.sphere_list.size--;
		}
	}
}*/

#pragma clang diagnostic pop
