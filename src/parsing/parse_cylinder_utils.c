/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_bool	check_cylinder_token_count(char **tokens)
{
	if (!tokens[1] || !tokens[2] || !tokens[3]
		|| !tokens[4] || !tokens[5] || tokens[6])
	{
		printf("Error\nCylinder requires exactly 5 parameters\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	parse_cylinder_geometry(char **tokens, t_cylinder *cyl)
{
	if (!parse_vector(tokens[1], &cyl->center)
		|| !parse_vector(tokens[2], &cyl->axis))
	{
		printf("Error\nInvalid cylinder center or axis\n");
		return (FALSE);
	}
	if (!is_normalized_vector(&cyl->axis))
	{
		printf("Error\nCylinder axis must be normalized\n");
		return (FALSE);
	}
	cyl->radius = parse_double(tokens[3]);
	cyl->height = parse_double(tokens[4]);
	if (cyl->radius == -999999.0 || cyl->radius <= 0
		|| cyl->height == -999999.0 || cyl->height <= 0)
	{
		printf("Error\nCylinder dimensions must be positive\n");
		return (FALSE);
	}
	return (TRUE);
}

t_cylinder	*allocate_cylinder(t_scene *scene)
{
	t_cylinder	*new_cylinders;

	new_cylinders = ft_realloc(scene->cylinders,
			sizeof(t_cylinder) * scene->cylinder_count,
			sizeof(t_cylinder) * (scene->cylinder_count + 1));
	if (!new_cylinders)
	{
		printf("Error\nMemory allocation failed\n");
		return (NULL);
	}
	scene->cylinders = new_cylinders;
	return (&scene->cylinders[scene->cylinder_count]);
}
