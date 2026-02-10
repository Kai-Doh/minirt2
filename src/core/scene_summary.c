/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_summary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	print_objects(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->sphere_count)
	{
		printf("  Sphere %d: center=(%.2f,%.2f,%.2f), radius=%.2f\n",
			scene->spheres[i].id, scene->spheres[i].center.x,
			scene->spheres[i].center.y, scene->spheres[i].center.z,
			scene->spheres[i].radius);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		printf("  Plane %d: point=(%.2f,%.2f,%.2f), normal=(%.2f,%.2f,%.2f)\n",
			scene->planes[i].id, scene->planes[i].point.x,
			scene->planes[i].point.y, scene->planes[i].point.z,
			scene->planes[i].normal.x, scene->planes[i].normal.y,
			scene->planes[i].normal.z);
		i++;
	}
}

static void	print_cylinders(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->cylinder_count)
	{
		printf("  Cylinder %d: center=(%.2f,%.2f,%.2f), ",
			scene->cylinders[i].id, scene->cylinders[i].center.x,
			scene->cylinders[i].center.y, scene->cylinders[i].center.z);
		printf("radius=%.2f, height=%.2f\n", scene->cylinders[i].radius,
			scene->cylinders[i].height);
		i++;
	}
}

void	print_scene_summary(t_scene *scene)
{
	printf("\n=== SCENE LOADED SUCCESSFULLY ===\n");
	printf("Camera: pos=(%.2f,%.2f,%.2f), dir=(%.2f,%.2f,%.2f), fov=%.2f\n",
		scene->camera.position.x, scene->camera.position.y,
		scene->camera.position.z, scene->camera.forward.x,
		scene->camera.forward.y, scene->camera.forward.z,
		scene->camera.fov);
	printf("Ambient: ratio=%.2f, color=(%.0f,%.0f,%.0f)\n",
		scene->ambient.ratio, scene->ambient.color.r * 255,
		scene->ambient.color.g * 255, scene->ambient.color.b * 255);
	printf("Light: pos=(%.2f,%.2f,%.2f), brightness=%.2f\n",
		scene->light.position.x, scene->light.position.y,
		scene->light.position.z, scene->light.brightness);
	printf("Objects: %d spheres, %d planes, %d cylinders\n",
		scene->sphere_count, scene->plane_count, scene->cylinder_count);
	print_objects(scene);
	print_cylinders(scene);
	printf("=================================\n");
}
