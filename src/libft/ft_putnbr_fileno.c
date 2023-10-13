/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: ft_putnbr_fileno.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/07 20:59:04                                            */
/*   Updated:  2023/10/13 17:36:30                                            */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <unistd.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static int	get_magnitude(long int n)
{
	int	magnitude;

	if (n == 0)
		return (1);
	magnitude = 0;
	while (n != 0)
	{
		if (magnitude == 0)
			magnitude = 1;
		else
			magnitude *= 10;
		n /= 10;
	}
	return (magnitude);
}

void	ft_putnbr_fileno(int fileno, int nbr)
{
	long int	n;
	size_t		i;
	int			magnitude;
	char		str[11];

	n = nbr;
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		i++;
		n = -n;
	}
	magnitude = get_magnitude(n);
	while (magnitude > 0)
	{
		str[i] = ((char)((n / magnitude) % 10)) + '0';
		magnitude /= 10;
		i++;
	}
	write(fileno, str, i);
}

#pragma clang diagnostic pop
