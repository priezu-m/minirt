/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: set_ambient_lightning.c                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/18 16:19:52                                            */
/*   Updated:  2023/10/19 21:32:35                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static bool	check_for_space_float(t_line *line, int i, bool *parsing_error, size_t lineno)
{
	if (!!ft_isspace(line->line[i]) == false)
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " floating point value does not match"
				" regex (-?[0-9]{0,19}(\\.[0-9]{1,18})?). Or is not separated\n"
				"by a space from the color descriptor.\n");
		return (false);
	}
	return (true);
}

static t_ambient_lighting	parse_lighting(t_line *line, bool *parsing_error, size_t lineno)
{
	t_ambient_lighting	ambient_lighting;
	int					i;

	i = 0;
	ambient_lighting.is_initialized = true;
	while (ft_isspace(line->line[i]) != false)
		i++;
	while (ft_isalpha(line->line[i]) != false)
		i++;
	while (ft_isspace(line->line[i]) != false)
		i++;
	ambient_lighting.ambient_lighting_intensity
		= parse_float(line, &i, parsing_error, lineno);
	if ((*parsing_error == true)
			|| (check_for_space_float(line, i, parsing_error, lineno) == false))
		return (ambient_lighting);
	while (ft_isspace(line->line[i]) != false)
		i++;
	ambient_lighting.color = parse_color(line, &i, parsing_error, lineno);
	return (ambient_lighting);
}

static void	set_ambient_lighting_internal(t_parameters *parameters, int fileno)
{
	t_buffer	buf;
	t_line		line;
	size_t		i;
	bool		parsing_error;

	i = 1;
	load_line_initial(&line, &buf, fileno);
	while (line.size > 0 && first_char_of_line(&line) != 'A')
	{
		load_line(&line, &buf, fileno);
		i++;
	}
	parameters->ambient_lighting = parse_lighting(&line, &parsing_error, i);
	if (parsing_error == true)
		parameters->parameters_valid = false;
}

void	set_ambient_lighting(char *filename, t_element_count element_count,
				t_parameters *parameters)
{
	const int		fileno = open(filename, O_RDONLY);

	if (parameters->parameters_valid == false)
		return ;
	if (element_count.ambient_lighting_count == 0)
	{
		parameters->ambient_lighting.is_initialized = false;
		return ;
	}
	if (fileno == -1)
	{
		perror("Error\nCould not open input file");
		parameters->parameters_valid = false;
		return ;
	}
	set_ambient_lighting_internal(parameters, fileno);
	close(fileno);
}

#pragma clang diagnostic pop
