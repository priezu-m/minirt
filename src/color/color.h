/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: color.h                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 23:50:07                                            */
/*   Updated:  2023/10/03 23:53:25                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}t_color;

#pragma clang diagnostic pop

#endif
