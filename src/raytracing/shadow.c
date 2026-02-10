/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	cyl_height_check(t_ray *sh, t_cylinder *cyl, double t)
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

static void	calc_cyl_abc(t_ray *sh, t_cylinder *cyl, double *abc)
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

static int	check_shadow_cyl(t_ray *sh, t_scene *scene, double light_d)
{
	int		i;
	double	abc[3];
	double	delta;
	double	t;

	i = -1;
	while (++i < scene->cylinder_count)
	{
		calc_cyl_abc(sh, &scene->cylinders[i], abc);
		delta = abc[1] * abc[1] - 4 * abc[0] * abc[2];
		if (delta < 0)
			continue ;
		t = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
		if (t > 0.001 && t < light_d
			&& cyl_height_check(sh, &scene->cylinders[i], t))
			return (1);
	}
	return (0);
}

static void	init_shadow_ray(t_ray *shadow, t_vector point, t_scene *scene,
		double *light_dist)
{
	t_vector	light_dir;

	light_dir.x = scene->light.position.x - point.x;
	light_dir.y = scene->light.position.y - point.y;
	light_dir.z = scene->light.position.z - point.z;
	*light_dist = vector_norm(light_dir);
	shadow->origin.x = point.x + light_dir.x * 0.001 / *light_dist;
	shadow->origin.y = point.y + light_dir.y * 0.001 / *light_dist;
	shadow->origin.z = point.z + light_dir.z * 0.001 / *light_dist;
	shadow->direction = vector_normalize(light_dir);
}

int	is_in_shadow(t_vector point, t_scene *scene)
{
	t_ray		shadow;
	double		light_dist;

	init_shadow_ray(&shadow, point, scene, &light_dist);
	if (check_shadow_sphere(&shadow, scene, light_dist))
		return (1);
	if (check_shadow_plane(&shadow, scene, light_dist))
		return (1);
	if (check_shadow_cyl(&shadow, scene, light_dist))
		return (1);
	return (0);
}
