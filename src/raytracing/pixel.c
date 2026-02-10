/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	calc_ray_dir(t_scene *scene, t_ray *ray, int x, int y)
{
	double		u;
	double		v;
	double		w;
	t_vector	dir_cam;

	u = -scene->viewport.width * 0.5 + (x + 0.5) * scene->viewport.px_x;
	v = scene->viewport.height * 0.5 - (y + 0.5) * scene->viewport.px_y;
	w = scene->camera.d;
	dir_cam = (t_vector){u, v, w};
	ray->direction = vector_normalize(change_base_ray(dir_cam, scene));
}

int	parse_pixel(t_scene *scene, t_ray *ray)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray->origin = scene->camera.position;
			calc_ray_dir(scene, ray, x, y);
			ray->pixel_x = x;
			ray->pixel_y = y;
			init_ray(ray, scene->camera.position, ray->direction);
			ray_intersec(ray, scene);
			y++;
		}
		x++;
	}
	return (1);
}
