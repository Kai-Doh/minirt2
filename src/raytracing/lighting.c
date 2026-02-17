/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector	get_sphere_normal(t_vector inter, t_sphere *sphere)
{
	t_vector	normal;

	normal.x = inter.x - sphere->center.x;
	normal.y = inter.y - sphere->center.y;
	normal.z = inter.z - sphere->center.z;
	return (vector_normalize(normal));
}

t_vector	get_plane_normal(t_plane *plane)
{
	return (vector_normalize(plane->normal));
}

t_vector	get_cylinder_normal(t_vector inter, t_cylinder *cyl)
{
	t_vector	cp;
	t_vector	proj;
	t_vector	normal;
	double		h;

	cp.x = inter.x - cyl->center.x;
	cp.y = inter.y - cyl->center.y;
	cp.z = inter.z - cyl->center.z;
	h = scalar_product(cp, cyl->axis);
	if (fabs(h - cyl->height / 2) < 0.001)
		return (cyl->axis);
	if (fabs(h + cyl->height / 2) < 0.001)
		return (vector_scale(cyl->axis, -1));
	proj = vector_scale(cyl->axis, h);
	normal.x = cp.x - proj.x;
	normal.y = cp.y - proj.y;
	normal.z = cp.z - proj.z;
	return (vector_normalize(normal));
}

t_vector	get_normal(t_ray *ray, t_scene *scene)
{
	t_vector	normal;
	t_vector	inter;
	int			id;

	normal = (t_vector){0, 0, 0};
	inter = ray->hit.inter;
	id = ray->hit.id;
	if (ray->hit.object_type == SPHERE)
		normal = get_sphere_normal(inter, &scene->spheres[id]);
	else if (ray->hit.object_type == PLANE)
		normal = get_plane_normal(&scene->planes[id]);
	else if (ray->hit.object_type == CYLINDER)
		normal = get_cylinder_normal(inter, &scene->cylinders[id]);
	return (normal);
}
