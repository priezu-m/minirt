/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parameters.h                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 21:56:50                                            */
/*   Updated:  2023/10/04 01:13:32                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H

# include <stdbool.h>
# include "../vector/vector.h"
# include "../coordinate/coordinate.h"
# include "../color/color.h"

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef struct s_ambient_lightning
{
	long double	ambient_lightning;
	t_color		color;
	bool		is_initialized;
}t_ambient_lightning;

typedef struct s_camera
{
	t_vector		orientation_vector;
	long double		field_of_view;
	t_coordinate	position;
	bool			is_initialized;
}t_camera;

typedef struct s_light
{
	t_coordinate	position;
	long double		brightness;
	t_color			color;
	bool			is_initialized;
}t_light;

typedef struct s_sphere
{
	t_coordinate	position;
	long double		diameter;
	t_color			color;
}t_sphere;

typedef struct s_sphere_list
{
	t_sphere	*sphere_list;
	int			size;
	bool		is_initialized;
}t_sphere_list;

typedef struct s_plane
{
	t_vector		orientation_vector;
	t_coordinate	position;
	t_color			color;
}t_plane;

typedef struct s_plane_list
{
	t_plane	*plane_list;
	int		size;
	bool	is_initialized;
}t_plane_list;

typedef struct s_cylinder
{
	t_vector		orientation_vector;
	t_coordinate	position;
	long double		height;
	long double		diameter;
	t_color			color;
}t_cylinder;

typedef struct s_cylider_list
{
	t_cylinder	*plane_list;
	int		size;
	bool	is_initialized;
}t_cylider_list;

typedef struct s_parametes
{
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_light				light;
	t_sphere_list		sphere_list;
	t_plane_list		plane_list;
	t_cylider_list		cylinder_list;
}t_parameters;

bool			parameter_file_valid(char *filename);
t_parameters	get_parameters(char *filename);
bool			parameters_valid(t_parameters parameters);
void			destroy_parameters(t_parameters parameters);
void			print_usage(void);

# pragma clang diagnostic pop

#endif
