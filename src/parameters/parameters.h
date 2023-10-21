/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parameters.h                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/03 21:56:50                                            */
/*   Updated:  2023/10/21 08:50:28                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H

# include <stdbool.h>
# include <stddef.h>
# include "../vector/vector.h"
# include "../coordinate/coordinate.h"
# include "../color/color.h"

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

# define MAX_LINE_SIZE 1000
# define BUFSIZE 10000

typedef struct s_line
{
	char	line[MAX_LINE_SIZE];
	int		size;
	bool	io_error;
}t_line;

typedef struct s_buffer
{
	int		size;
	int		index;
	char	buf[BUFSIZE];
	bool	io_error;
}t_buffer;

typedef struct s_ambient_lighting
{
	long double	ambient_lighting_intensity;
	t_color		color;
	bool		is_initialized;
}t_ambient_lighting;

typedef struct s_camera
{
	t_vector		orientation_vector;
	long double		field_of_view;
	t_coordinate	position;
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
	t_cylinder	*cylinder_list;
	int			size;
}t_cylider_list;

typedef struct s_parametes
{
	t_ambient_lighting	ambient_lighting;
	t_camera			camera;
	t_light				light;
	t_sphere_list		sphere_list;
	t_plane_list		plane_list;
	t_cylider_list		cylinder_list;
	bool				parameters_valid;
}t_parameters;

typedef struct s_element_count
{
	int		ambient_lighting_count;
	int		camera_count;
	int		light_count;
	int		sphere_count;
	int		plane_count;
	int		cylinder_count;
	bool	count_failed;
}t_element_count;

t_parameters	get_parameters(char *filename);
bool			parameters_valid(t_parameters parameters);
void			destroy_parameters(t_parameters parameters);
void			print_usage(void);
t_element_count	count_elements(char *filename);
void			load_line(t_line *line, t_buffer *buf, int fileno);
bool			is_valid_id(const char **valid_element_ids, t_line *line);
void			add_to_count_helper(t_line *line,
					t_element_count *element_count, size_t lineno);
t_parameters	get_parameters_internal(char *filename,
					t_element_count element_count);
void			set_ambient_lighting(char *filename,
					t_element_count element_count, t_parameters *parameters);
long double		parse_float(t_line *line, int *i, bool *parsing_error,
					size_t lineno);
t_color			parse_color(t_line *line, int *i, bool *parsing_error,
					size_t lineno);
char			first_char_of_line(t_line *line);
void			load_line_initial(t_line *line, t_buffer *buf, int fileno);
void			set_camera(char *filename, t_parameters *parameters);
t_coordinate	parse_coordinates(t_line *line, int *i, bool *parsing_error,
					size_t lineno);
t_vector		parse_orientation_vector(t_line *line, int *i,
					bool *parsing_error, size_t lineno);
void			set_light(char *filename, t_element_count element_count,
					t_parameters *parameters);
void			set_sphere_list(char *filename, t_element_count element_count,
					t_parameters *parameters);
void			set_plane_list(char *filename, t_element_count element_count,
					t_parameters *parameters);
void		set_cylinder_list(char *filename, t_element_count element_count,
					t_parameters *parameters);
t_cylinder	parse_cylinder(t_line *line, bool *parsing_error,
								size_t lineno);

# pragma clang diagnostic pop

#endif
