/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.c                                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/25 17:27:48                                            */
/*   Updated:  2023/10/04 01:59:36                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters/parameters.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

int	main(int argc, char **argv)
{
	t_parameters	parameters;
	if (argc != 2)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (parameter_file_valid(argv[1]) == false)
		return (EXIT_FAILURE);
	parameters = get_parameters(argv[1]);
	if (parameters_valid(parameters) == false)
	{
		destroy_parameters(parameters);
		ft_putstr("Error\n not enough memory to run the program.\n");
		return (EXIT_FAILURE);
	}
	destroy_parameters(parameters);
	return (EXIT_SUCCESS);
}

#pragma clang diagnostic pop
