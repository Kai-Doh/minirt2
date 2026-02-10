/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_bool	validate_plane_params(char **tokens, t_plane *plane)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		printf("Error\nPlane requires exactly 3 parameters\n");
		return (FALSE);
	}
	if (!parse_vector(tokens[1], &plane->point)
		|| !parse_vector(tokens[2], &plane->normal)
		|| !parse_color(tokens[3], &plane->color))
	{
		printf("Error\nInvalid plane parameters\n");
		return (FALSE);
	}
	if (!is_normalized_vector(&plane->normal))
	{
		printf("Error\nPlane normal must be normalized\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*new_planes;
	t_plane	*plane;

	new_planes = ft_realloc(scene->planes,
			sizeof(t_plane) * scene->plane_count,
			sizeof(t_plane) * (scene->plane_count + 1));
	if (!new_planes)
	{
		printf("Error\nMemory allocation failed\n");
		return (FALSE);
	}
	scene->planes = new_planes;
	plane = &scene->planes[scene->plane_count];
	if (!validate_plane_params(tokens, plane))
		return (FALSE);
	plane->id = scene->plane_count;
	scene->plane_count++;
	return (TRUE);
}

static t_bool	validate_cylinder_params(char **tokens, t_cylinder *cyl)
{
	if (!check_cylinder_token_count(tokens))
		return (FALSE);
	if (!parse_cylinder_geometry(tokens, cyl))
		return (FALSE);
	if (!parse_color(tokens[5], &cyl->color))
	{
		printf("Error\nInvalid cylinder color\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = allocate_cylinder(scene);
	if (!cylinder)
		return (FALSE);
	if (!validate_cylinder_params(tokens, cylinder))
		return (FALSE);
	cylinder->id = scene->cylinder_count;
	scene->cylinder_count++;
	return (TRUE);
}
