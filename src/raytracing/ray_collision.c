/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_color	get_obj_color(t_ray *ray, t_scene *scene)
{
	t_color	rgb;

	rgb = (t_color){0, 0, 0};
	if (ray->hit.object_type == SPHERE)
		rgb = scene->spheres[ray->hit.id].color;
	else if (ray->hit.object_type == PLANE)
		rgb = scene->planes[ray->hit.id].color;
	else if (ray->hit.object_type == CYLINDER)
		rgb = scene->cylinders[ray->hit.id].color;
	return (rgb);
}

static double	calc_diffuse(t_ray *ray, t_scene *scene, t_vector normal)
{
	t_vector	light_dir;
	double		n_dot_l;

	light_dir.x = scene->light.position.x - ray->hit.inter.x;
	light_dir.y = scene->light.position.y - ray->hit.inter.y;
	light_dir.z = scene->light.position.z - ray->hit.inter.z;
	light_dir = vector_normalize(light_dir);
	n_dot_l = scalar_product(normal, light_dir);
	if (n_dot_l < 0)
		n_dot_l = 0;
	return (n_dot_l * scene->light.brightness);
}

static t_color	apply_lighting(t_ray *ray, t_scene *scene)
{
	t_color		obj_color;
	t_vector	normal;
	double		ambient;
	double		diffuse;
	t_color		result;

	obj_color = get_obj_color(ray, scene);
	normal = get_normal(ray, scene);
	ambient = scene->ambient.ratio;
	diffuse = 0;
	if (!is_in_shadow(ray->hit.inter, scene, &ray->hit))
		diffuse = calc_diffuse(ray, scene, normal);
	result.r = obj_color.r * (ambient + diffuse);
	result.g = obj_color.g * (ambient + diffuse);
	result.b = obj_color.b * (ambient + diffuse);
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	return (result);
}

int	ray_intersec(t_ray *ray, t_scene *scene)
{
	t_color	rgb;
	int		color;

	intersec_spheres(ray, scene);
	intersec_planes(ray, scene);
	intersec_cylinders(ray, scene);
	if (ray->hit.hit == TRUE)
	{
		rgb = apply_lighting(ray, scene);
		color = rgb_to_int(rgb);
		mlx_pixel_put(scene->mlx, scene->mlx_win, ray->pixel_x,
			ray->pixel_y, color);
		return (1);
	}
	mlx_pixel_put(scene->mlx, scene->mlx_win, ray->pixel_x,
		ray->pixel_y, 0x000000);
	return (1);
}
