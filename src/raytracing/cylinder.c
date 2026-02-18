/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	get_cylinder_abc(t_cylinder *cyl, t_ray *ray, double *abc)
{
	t_vector	oc;
	double		d_dot_v;
	double		oc_dot_v;

	oc.x = ray->origin.x - cyl->center.x;
	oc.y = ray->origin.y - cyl->center.y;
	oc.z = ray->origin.z - cyl->center.z;
	d_dot_v = scalar_product(ray->direction, cyl->axis);
	oc_dot_v = scalar_product(oc, cyl->axis);
	abc[0] = scalar_product(ray->direction, ray->direction) - d_dot_v * d_dot_v;
	abc[1] = 2 * (scalar_product(ray->direction, oc) - d_dot_v * oc_dot_v);
	abc[2] = scalar_product(oc, oc) - oc_dot_v * oc_dot_v
		- cyl->radius * cyl->radius;
}

static int	check_cyl_height(t_cylinder *cyl, t_ray *ray, double t)
{
	t_vector	p;
	t_vector	cp;
	double		h;

	p = point_value(ray, t);
	cp.x = p.x - cyl->center.x;
	cp.y = p.y - cyl->center.y;
	cp.z = p.z - cyl->center.z;
	h = scalar_product(cp, cyl->axis);
	if (h >= -cyl->height / 2 && h <= cyl->height / 2)
		return (1);
	return (0);
}

static double	get_cyl_t(t_cylinder *cyl, t_ray *ray, double *abc)
{
	double	delta;
	double	t1;
	double	t2;

	if (fabs(abc[0]) < 1e-12)
		return (-1);
	delta = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (delta < 0)
		return (-1);
	t1 = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	t2 = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	if (t1 > 0.001 && check_cyl_height(cyl, ray, t1))
		return (t1);
	if (t2 > 0.001 && check_cyl_height(cyl, ray, t2))
		return (t2);
	return (-1);
}

static void	update_cyl_hit(t_ray *ray, t_scene *scene, int i, double t)
{
	ray->hit.hit = TRUE;
	ray->hit.inter = point_value(ray, t);
	ray->hit.object = (void *)&scene->cylinders[i];
	ray->hit.id = i;
	ray->hit.object_type = CYLINDER;
	ray->hit.delta = t;
}

int	intersec_cylinders(t_ray *ray, t_scene *scene)
{
	int		i;
	double	abc[3];
	double	t[2];
	double	closest_t;

	i = -1;
	closest_t = ray->hit.delta;
	if (closest_t == 0)
		closest_t = -1;
	while (++i < scene->cylinder_count)
	{
		get_cylinder_abc(&scene->cylinders[i], ray, abc);
		t[0] = get_cyl_t(&scene->cylinders[i], ray, abc);
		t[1] = intersect_caps(&scene->cylinders[i], ray);
		if (t[1] > 0.001 && (t[0] < 0.001 || t[1] < t[0]))
			t[0] = t[1];
		if (t[0] > 0.001 && (closest_t < 0 || t[0] < closest_t))
		{
			closest_t = t[0];
			update_cyl_hit(ray, scene, i, t[0]);
		}
	}
	return (1);
}
