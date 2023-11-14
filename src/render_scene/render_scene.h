/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: render_scene.h                                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/22 13:33:30                                            */
/*   Updated:  2023/11/14 23:24:40                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_SCENE_H
# define RENDER_SCENE_H

# include "../parameters/parameters.h"

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef enum e_shape_type
{
	e_sphere,
	e_plane,
	e_cylinder
}t_shape_type;

void			render_scene(t_parameters parameters);
void			render_scene_in_buffer(t_parameters parameters,
					unsigned int *buffer, int height, int width);
unsigned int	get_ray_color(t_vector ray_direction, t_parameters parameters);
bool			direct_light(t_shape_type shape_type, int i,
					t_vector intersection_point, t_parameters parameters);
t_color			check_cylinder_intersection_color(t_parameters parameters,
					t_vector ray_direction, long double *min_t, t_color color);
t_color			check_sphere_intersection_color(t_parameters parameters,
					t_vector ray_direction, long double *min_t, t_color color);
t_color			check_plane_intersection_color(t_parameters parameters,
					t_vector ray_direction, long double *min_t, t_color color);

# pragma clang diagnostic pop

#endif
