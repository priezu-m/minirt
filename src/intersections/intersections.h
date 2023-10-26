/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: intersections.h                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/26 09:02:32                                            */
/*   Updated:  2023/10/26 09:30:56                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef  INTERSECTIONS_H
# define  INTERSECTIONS_H

# include "../parameters/parameters.h"

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_intersection
{
	long double	t1;
	long double	t2;
}t_intersections;

long double	intersect_ray_sphere(t_vector3 ray_direction, t_vector3 origin,
				t_sphere sphere);

# pragma clang diagnostic pop

#endif
