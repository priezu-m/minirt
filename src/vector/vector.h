/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: vector.h                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 23:44:35                                            */
/*   Updated:  2023/10/07 20:33:40                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_vector
{
	long double	x;
	long double	y;
	long double	z;
}t_vector;

# pragma clang diagnostic pop

#endif
