/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	check_shadow_sphere(t_ray *sh, t_scene *scene, double light_d)
{
	int			i;
	t_vector	oc;
	double		abc[3];
	double		delta;
	double		t;

	i = -1;
	while (++i < scene->sphere_count)
	{
		oc.x = sh->origin.x - scene->spheres[i].center.x;
		oc.y = sh->origin.y - scene->spheres[i].center.y;
		oc.z = sh->origin.z - scene->spheres[i].center.z;
		abc[0] = scalar_product(sh->direction, sh->direction);
		abc[1] = 2 * scalar_product(sh->direction, oc);
		abc[2] = scalar_product(oc, oc) - ft_sqr(scene->spheres[i].radius);
		delta = abc[1] * abc[1] - 4 * abc[0] * abc[2];
		if (delta < 0)
			continue ;
		t = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
		if (t > 0.001 && t < light_d)
			return (1);
	}
	return (0);
}

int	cyl_height_check(t_ray *sh, t_cylinder *cyl, double t)
{
	t_vector	p;
	t_vector	cp;
	double		h;

	p.x = sh->origin.x + sh->direction.x * t;
	p.y = sh->origin.y + sh->direction.y * t;
	p.z = sh->origin.z + sh->direction.z * t;
	cp.x = p.x - cyl->center.x;
	cp.y = p.y - cyl->center.y;
	cp.z = p.z - cyl->center.z;
	h = scalar_product(cp, cyl->axis);
	return (h >= -cyl->height / 2 && h <= cyl->height / 2);
}

void	calc_cyl_abc(t_ray *sh, t_cylinder *cyl, double *abc)
{
	t_vector	oc;

	oc = (t_vector){sh->origin.x - cyl->center.x,
		sh->origin.y - cyl->center.y, sh->origin.z - cyl->center.z};
	abc[0] = scalar_product(sh->direction, sh->direction)
		- ft_sqr(scalar_product(sh->direction, cyl->axis));
	abc[1] = 2 * (scalar_product(sh->direction, oc)
			- scalar_product(sh->direction, cyl->axis)
			* scalar_product(oc, cyl->axis));
	abc[2] = scalar_product(oc, oc) - ft_sqr(scalar_product(oc, cyl->axis))
		- ft_sqr(cyl->radius);
}

int	check_shadow_plane(t_ray *shadow, t_scene *scene, double light_d)
{
	int		i;
	double	den;
	double	t;

	i = 0;
	while (i < scene->plane_count)
	{
		den = scalar_product(scene->planes[i].normal, shadow->direction);
		if (fabs(den) > 1e-12)
		{
			t = scalar_product((t_vector){scene->planes[i].point.x
					- shadow->origin.x, scene->planes[i].point.y
					- shadow->origin.y, scene->planes[i].point.z
					- shadow->origin.z}, scene->planes[i].normal) / den;
			if (t > 0.001 && t < light_d)
				return (1);
		}
		i++;
	}
	return (0);
}
