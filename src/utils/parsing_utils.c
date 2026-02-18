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

/* Parses fractional part of a double string */
static double	parse_frac(char *str, int i)
{
	double	frac;
	double	divisor;

	frac = 0.0;
	divisor = 10.0;
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		frac += (double)(str[i] - '0') / divisor;
		divisor *= 10.0;
		i++;
	}
	return (frac);
}

/* Parses string to double or returns -999999.0 */
double	parse_double(char *str)
{
	double	result;
	int		sign;
	int		i;

	if (!is_valid_double(str))
		return (-999999.0);
	result = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] != '.')
		result = result * 10.0 + (double)(str[i++] - '0');
	return (sign * (result + parse_frac(str, i)));
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
