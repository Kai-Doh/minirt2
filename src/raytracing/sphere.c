/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Returns the point on a ray at parameter t */
t_vector	point_value(t_ray *ray, double t)
{
	t_vector	point;

	point.x = ray->origin.x + ray->direction.x * t;
	point.y = ray->origin.y + ray->direction.y * t;
	point.z = ray->origin.z + ray->direction.z * t;
	return (point);
}

/* Returns the nearest positive intersection t */
static double	get_sphere_t(double a, double b, double discr)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(discr)) / (2 * a);
	t2 = (-b + sqrt(discr)) / (2 * a);
	if (t1 > 0.001 && t2 > 0.001)
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	if (t1 > 0.001)
		return (t1);
	if (t2 > 0.001)
		return (t2);
	return (-1);
}

/* Computes sphere intersection discriminant */
static double	calc_sphere_discr(t_sphere *sp, t_ray *ray, double *abc)
{
	double	ox;
	double	oy;
	double	oz;

	ox = ray->origin.x - sp->center.x;
	oy = ray->origin.y - sp->center.y;
	oz = ray->origin.z - sp->center.z;
	abc[0] = ft_sqr(ray->direction.x) + ft_sqr(ray->direction.y)
		+ ft_sqr(ray->direction.z);
	abc[1] = 2 * (ray->direction.x * ox + ray->direction.y * oy
			+ ray->direction.z * oz);
	abc[2] = ft_sqr(ox) + ft_sqr(oy) + ft_sqr(oz) - ft_sqr(sp->radius);
	return (abc[1] * abc[1] - 4 * abc[0] * abc[2]);
}

/* Updates ray hit data for a sphere intersection */
static void	update_sphere_hit(t_ray *ray, t_scene *scene, int i, double t)
{
	ray->hit.hit = TRUE;
	ray->hit.inter = point_value(ray, t);
	ray->hit.object = (void *)&scene->spheres[i];
	ray->hit.id = i;
	ray->hit.object_type = SPHERE;
	ray->hit.delta = t;
}

/* Finds nearest sphere intersected by the ray */
int	intersec_spheres(t_ray *ray, t_scene *scene)
{
	int		i;
	double	closest_t;
	double	abc[3];
	double	discr;
	double	t;

	i = -1;
	closest_t = ray->hit.delta;
	while (++i < scene->sphere_count)
	{
		discr = calc_sphere_discr(&scene->spheres[i], ray, abc);
		if (discr < 0)
			continue ;
		t = get_sphere_t(abc[0], abc[1], discr);
		if (t > 0.001 && (closest_t < 0 || t < closest_t))
		{
			closest_t = t;
			update_sphere_hit(ray, scene, i, t);
		}
	}
	return (1);
}
