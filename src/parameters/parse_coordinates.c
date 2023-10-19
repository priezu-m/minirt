/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parse_coordinates.c                                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/19 21:52:02                                            */
/*   Updated:  2023/10/19 23:05:11                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

t_coordinate	 parse_coordinates(t_line *line, int *i, bool *parsing_error,
					size_t lineno)
{
	t_coordinate	coordinates;

	coordinates.x = parse_float(line, i, parsing_error, lineno);
	if (*parsing_error == true)
		return (coordinates);
	if (line->line[*i] != ',')
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " coordinates are not three floating "
				"point values separated by comas\n");
		return (coordinates);
	}
	(*i)++;
	coordinates.y = parse_float(line, i, parsing_error, lineno);
	if (*parsing_error == true)
		return (coordinates);
	if (line->line[*i] != ',')
	{
		*parsing_error = true;
		ft_putstr_fileno(STDERR_FILENO, "Error\nline ");
		ft_putnbr_fileno(STDERR_FILENO, lineno);
		ft_putstr_fileno(STDERR_FILENO, " coordinates are not three floating "
				"point values separated by comas\n");
		return (coordinates);
	}
	(*i)++;
	coordinates.z = parse_float(line, i, parsing_error, lineno);
	return (coordinates);
}

#pragma clang diagnostic pop
