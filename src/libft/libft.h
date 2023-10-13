/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: libft.h                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/10/04 01:13:48                                            */
/*   Updated:  2023/10/07 20:34:02                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

void	ft_putstr(const char *str);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isspace(char c);
void	ft_putstr_fileno(int fileno, const char *str);
void	ft_putnbr_fileno(int fileno, int nbr);

# pragma clang diagnostic pop

#endif
