/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Initializes world basis vectors (forward/right/up) */
int	init_base_world(t_base_world *base)
{
	base->forward = (t_vector){0, 0, 1};
	base->right = (t_vector){1, 0, 0};
	base->up = (t_vector){0, 1, 0};
	return (1);
}

/* Returns 1 if forward vector is parallel to world up */
static int	is_parallel_up(t_vector forward)
{
	double	dot;

	dot = fabs(forward.x * 0 + forward.y * 1 + forward.z * 0);
	if (dot > 0.999)
		return (1);
	return (0);
}

/* Builds camera right and up vectors from forward */
int	make_base_cam(t_scene *scene)
{
	t_vector	world_up;

	world_up = (t_vector){0, 1, 0};
	scene->camera.forward = vector_normalize(scene->camera.forward);
	if (is_parallel_up(scene->camera.forward))
		world_up = (t_vector){0, 0, 1};
	scene->camera.right = vector_normalize(
			vector_product(world_up, scene->camera.forward));
	scene->camera.up = vector_normalize(
			vector_product(scene->camera.forward, scene->camera.right));
	return (1);
}

/* Sets up the complete camera orientation basis */
int	make_orientation_cam(t_scene *scene)
{
	init_base_world(&scene->base_world);
	scene->camera.forward = vector_normalize(scene->camera.forward);
	if (!make_base_cam(scene))
		return (0);
	return (1);
}
