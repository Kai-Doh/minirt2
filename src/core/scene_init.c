/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_scene(t_scene *scene)
{
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->ambient_count = 0;
	scene->camera_count = 0;
	scene->light_count = 0;
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
	scene->mlx = NULL;
	scene->mlx_win = NULL;
}

void	cleanup_scene(t_scene *scene)
{
	if (scene->spheres)
		free(scene->spheres);
	if (scene->planes)
		free(scene->planes);
	if (scene->cylinders)
		free(scene->cylinders);
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
}
