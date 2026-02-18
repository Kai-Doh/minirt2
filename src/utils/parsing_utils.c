/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:50:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/09/09 14:50:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Returns TRUE if string is a valid double literal */
t_bool	is_valid_double(char *str)
{
	int	i;
	int	dot_count;

	if (!str || !str[0])
		return (FALSE);
	i = 0;
	dot_count = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '.' && ++dot_count == 1)
			i++;
		else if (!ft_isdigit(str[i]))
			return (FALSE);
		else
			i++;
	}
	return (dot_count <= 1);
}

/* Parses string to double or returns -999999.0 */
double	parse_double(char *str)
{
	double	result;
	char	*endptr;

	if (!is_valid_double(str))
		return (-999999.0);
	result = strtod(str, &endptr);
	if (*endptr != '\0')
		return (-999999.0);
	return (result);
}

/* Frees a null-terminated array of strings */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
