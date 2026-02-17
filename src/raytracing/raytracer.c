/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	close_window(t_scene *scene)
{
	if (scene->mlx_win)
		mlx_destroy_window(scene->mlx, scene->mlx_win);
	mlx_cleanup(scene);
	cleanup_scene(scene);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_scene *scene)
{
	if (keycode == 65307 || keycode == 53)
		close_window(scene);
	return (0);
}

t_vector	change_base_ray(t_vector v, t_scene *scene)
{
	t_vector	result;
	t_camera	cam;

	cam = scene->camera;
	result.x = v.x * cam.right.x + v.y * cam.up.x + v.z * cam.forward.x;
	result.y = v.x * cam.right.y + v.y * cam.up.y + v.z * cam.forward.y;
	result.z = v.x * cam.right.z + v.y * cam.up.z + v.z * cam.forward.z;
	return (result);
}

int	raytracer(t_scene *scene, t_ray *ray)
{
	if (!init_mlx(scene))
		return (0);
	if (!make_orientation_cam(scene))
		return (0);
	if (!init_viewport(scene))
		return (0);
	mlx_key_hook(scene->mlx_win, (void *)handle_key, scene);
	mlx_hook(scene->mlx_win, 17, 0, (void *)close_window, scene);
	if (!parse_pixel(scene, ray))
	{
		close_window(scene);
		return (0);
	}
	mlx_loop(scene->mlx);
	return (1);
}
