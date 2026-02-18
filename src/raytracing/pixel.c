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

static void	render_one_column(t_scene *s, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		s->current_ray.origin = s->camera.position;
		calc_ray_dir(s, &s->current_ray, x, y);
		s->current_ray.pixel_x = x;
		s->current_ray.pixel_y = y;
		init_ray(&s->current_ray, s->camera.position,
			s->current_ray.direction);
		ray_intersec(&s->current_ray, s);
		y++;
	}
}

int	render_pixel_step(t_scene *scene)
{
	if (scene->render_x >= WIDTH)
		return (0);
	render_one_column(scene, scene->render_x);
	scene->render_x++;
	if (scene->render_x >= WIDTH)
		mlx_put_image_to_window(scene->mlx, scene->mlx_win,
			scene->img, 0, 0);
	return (0);
}
