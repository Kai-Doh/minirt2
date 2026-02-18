/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Checks if filename ends with .rt extension */
static t_bool	check_rt_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (FALSE);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
}

/* Validates argument count and .rt file extension */
t_bool	arg_check(int ac, char **av)
{
	if (ac < 2)
	{
		write(2, ARG_INVALID_MINUS, ft_strlen(ARG_INVALID_MINUS));
		write(2, ARG_USAGE, ft_strlen(ARG_USAGE));
		return (FALSE);
	}
	else if (ac > 2)
	{
		write(2, ARG_INVALID_PLUS, ft_strlen(ARG_INVALID_PLUS));
		write(2, ARG_USAGE, ft_strlen(ARG_USAGE));
		return (FALSE);
	}
	if (!check_rt_extension(av[1]))
	{
		write(2, FILE_INVALID, ft_strlen(FILE_INVALID));
		return (FALSE);
	}
	return (TRUE);
}
