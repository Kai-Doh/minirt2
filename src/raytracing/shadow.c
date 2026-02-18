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

static int	test_one_cyl(t_ray *sh, t_cylinder *cyl, double light_d)
{
	double	abc[3];
	double	delta;
	double	t[2];

	t[0] = intersect_caps(cyl, sh);
	if (t[0] > 0.001 && t[0] < light_d)
		return (1);
	calc_cyl_abc(sh, cyl, abc);
	if (fabs(abc[0]) < 1e-12)
		return (0);
	delta = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (delta < 0)
		return (0);
	t[0] = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
	if (t[0] > 0.001 && t[0] < light_d && cyl_height_check(sh, cyl, t[0]))
		return (1);
	if (t[1] > 0.001 && t[1] < light_d && cyl_height_check(sh, cyl, t[1]))
		return (1);
	return (0);
}

static int	check_shadow_cyl(t_ray *sh, t_scene *scene, double light_d,
		int skip_idx)
{
	int	i;

	i = -1;
	while (++i < scene->cylinder_count)
	{
		if (i == skip_idx)
			continue ;
		if (test_one_cyl(sh, &scene->cylinders[i], light_d))
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
	if (*light_dist < 1e-12)
	{
		shadow->direction = (t_vector){0, 0, 0};
		return ;
	}
	shadow->origin.x = point.x + light_dir.x * 0.001 / *light_dist;
	shadow->origin.y = point.y + light_dir.y * 0.001 / *light_dist;
	shadow->origin.z = point.z + light_dir.z * 0.001 / *light_dist;
	shadow->direction = vector_normalize(light_dir);
}

int	is_in_shadow(t_vector point, t_scene *scene, t_hit *hit)
{
	t_ray		shadow;
	double		light_dist;
	int			skip_idx;

	init_shadow_ray(&shadow, point, scene, &light_dist);
	if (light_dist < 1e-12)
		return (0);
	skip_idx = -1;
	if (hit->object_type == CYLINDER)
		skip_idx = hit->id;
	if (check_shadow_sphere(&shadow, scene, light_dist))
		return (1);
	if (check_shadow_plane(&shadow, scene, light_dist))
		return (1);
	if (check_shadow_cyl(&shadow, scene, light_dist, skip_idx))
		return (1);
	return (0);
}
