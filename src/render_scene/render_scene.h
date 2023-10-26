/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: render_scene.h                                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/22 13:33:30                                            */
/*   Updated:  2023/10/26 08:49:53                                            */
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

void			render_scene(t_parameters parameters);
void			render_scene_in_buffer(t_parameters parameters,
					unsigned int *buffer, int height, int width);
unsigned int	get_ray_color(t_vector3 ray_direction, t_parameters parameters);

# pragma clang diagnostic pop

#endif
