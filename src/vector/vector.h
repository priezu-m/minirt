/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: vector.h                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 23:44:35                                            */
/*   Updated:  2023/10/26 07:58:39                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_vector3
{
	long double	x;
	long double	y;
	long double	z;
}t_vector3;

bool		is_normal_vector3(t_vector3 vector3);
t_vector3	normalize_vector3(t_vector3 v1);
t_vector3	cross_product_vector3(t_vector3 v1, t_vector3 v2);
t_vector3	vector3_multiply(t_vector3 v1, long double s);
t_vector3	vector3_substract(t_vector3 v1, t_vector3 v2);
t_vector3	vector3_add(t_vector3 v1, t_vector3 v2);
long double	get_magnitude_vector3(t_vector3 v1);
long double	dot_product_vector3(t_vector3 v1, t_vector3 v2);

# pragma clang diagnostic pop

#endif
