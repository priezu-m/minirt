/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersections.h                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 09:02:32                                            */
/*   Updated:  2023/11/12 18:04:02                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "../parameters/parameters.h"

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_intersection
{
	long double	distance;
	t_vector	point;
	t_vector	surface_normal;
}t_intersection;	

t_intersection	intersect_ray_sphere(t_vector ray_direction, t_vector origin,
					t_sphere sphere);
long double		intersect_ray_cylinder(t_vector ray_direction, t_vector origin,
					t_cylinder cylinder);
long double		intersect_ray_plane(t_vector ray_direction, t_vector origin,
					t_plane plane);

# pragma clang diagnostic pop

#endif
