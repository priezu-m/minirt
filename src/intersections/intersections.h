/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersections.h                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 09:02:32                                            */
/*   Updated:  2023/11/14 19:39:44                                            */
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

typedef struct s_discriminant
{
	long double	a;
	long double	b;
	long double	c;
	long double	bb_4ac;

}t_discriminant;

typedef struct s_intersec_ray_cylinder_data
{
	long double		*distance;
	t_vector		origin;
	t_cylinder		cylinder;
	t_intersection	*intersections;
	t_vector		ray_direction;
	t_discriminant	discriminant;
	t_vector		lid_center;
	long double		m;
}t_intersect_ray_cylinder_data;

t_intersection	intersect_ray_sphere(t_vector ray_direction, t_vector origin,
					t_sphere sphere);
t_intersection	intersect_ray_cylinder(t_vector ray_direction, t_vector origin,
					t_cylinder cylinder);
t_intersection	intersect_ray_plane(t_vector ray_direction, t_vector origin,
					t_plane plane);
t_intersection	intersect_ray_cylinder_helper(
					t_intersect_ray_cylinder_data data);
t_intersection	check_intersection_whit_lid(t_vector ray_direction,
					t_vector origin, t_cylinder cylinder);

# pragma clang diagnostic pop

#endif
