/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Computes the D constant of the plane equation */
static double	value_d(t_vector n, t_vector p)
{
	double	result;

	result = -(n.x * p.x + n.y * p.y + n.z * p.z);
	return (result);
}

/* Returns the ray-plane intersection distance t */
static double	calc_plane_t(t_plane *plane, t_ray *ray)
{
	double	num;
	double	den;
	double	d;

	d = value_d(plane->normal, plane->point);
	num = scalar_product(plane->normal, ray->origin) + d;
	den = scalar_product(plane->normal, ray->direction);
	if (fabs(den) < 1e-12)
		return (-1);
	return (-num / den);
}

/* Finds the nearest plane intersected by the ray */
int	intersec_planes(t_ray *ray, t_scene *scene)
{
	int		i;
	double	t;
	double	closest_t;

	i = 0;
	closest_t = ray->hit.delta;
	if (closest_t == 0)
		closest_t = -1;
	while (i < scene->plane_count)
	{
		t = calc_plane_t(&scene->planes[i], ray);
		if (t > 0.001 && (closest_t < 0 || t < closest_t))
		{
			closest_t = t;
			ray->hit.hit = TRUE;
			ray->hit.inter = point_value(ray, t);
			ray->hit.object = (void *)&scene->planes[i];
			ray->hit.id = i;
			ray->hit.object_type = PLANE;
			ray->hit.delta = closest_t;
		}
		i++;
	}
	return (1);
}
