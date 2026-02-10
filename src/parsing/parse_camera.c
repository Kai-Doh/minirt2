/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_bool	validate_camera_vectors(char **tokens, t_scene *scene)
{
	if (!parse_vector(tokens[1], &scene->camera.position))
	{
		printf("Error\nInvalid camera position\n");
		return (FALSE);
	}
	if (!parse_vector(tokens[2], &scene->camera.forward))
	{
		printf("Error\nInvalid camera orientation\n");
		return (FALSE);
	}
	if (!is_normalized_vector(&scene->camera.forward))
	{
		printf("Error\nCamera orientation must be normalized\n");
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	validate_camera_params(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		printf("Error\nCamera requires exactly 3 parameters\n");
		return (FALSE);
	}
	if (!validate_camera_vectors(tokens, scene))
		return (FALSE);
	scene->camera.fov = parse_double(tokens[3]);
	if (scene->camera.fov == -999999.0 || scene->camera.fov < 0
		|| scene->camera.fov > 180)
	{
		printf("Error\nCamera FOV must be [0,180]\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	parse_camera(char **tokens, t_scene *scene)
{
	if (!validate_camera_params(tokens, scene))
		return (FALSE);
	scene->camera_count++;
	return (TRUE);
}
