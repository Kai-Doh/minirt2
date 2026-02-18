/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Parses a comma-separated string into a t_vector */
t_bool	parse_vector(char *str, t_vector *vec)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (FALSE);
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		return (FALSE);
	}
	vec->x = parse_double(split[0]);
	vec->y = parse_double(split[1]);
	vec->z = parse_double(split[2]);
	free_split(split);
	if (vec->x == -999999.0 || vec->y == -999999.0 || vec->z == -999999.0)
		return (FALSE);
	return (TRUE);
}

/* Checks that r, g, b components are in [0,255] */
static t_bool	validate_color_values(double r, double g, double b)
{
	if (r == -999999.0 || g == -999999.0 || b == -999999.0)
		return (FALSE);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FALSE);
	return (TRUE);
}

/* Splits color string and parses r, g, b values */
static t_bool	parse_color_components(char *str, double *r, double *g,
		double *b)
{
	char	**split;
	int		len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		if (split)
			free_split(split);
		return (FALSE);
	}
	*r = parse_double(split[0]);
	*g = parse_double(split[1]);
	*b = parse_double(split[2]);
	free_split(split);
	return (TRUE);
}

/* Parses a comma-separated string into a t_color */
t_bool	parse_color(char *str, t_color *color)
{
	double	r;
	double	g;
	double	b;

	if (!parse_color_components(str, &r, &g, &b))
		return (FALSE);
	if (!validate_color_values(r, g, b))
		return (FALSE);
	color->r = r;
	color->g = g;
	color->b = b;
	return (TRUE);
}
