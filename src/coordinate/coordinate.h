/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: coordinate.h                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 23:41:38                                            */
/*   Updated:  2023/10/03 23:44:19                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORDINATE_H
# define COORDINATE_H

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_coordinate
{
	long double	x;
	long double	y;
	long double	z;
}t_coordinate;

# pragma clang diagnostic pop

#endif
