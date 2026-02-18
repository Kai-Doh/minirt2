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

/* Returns the base color of the intersected object */
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

/* Calculates diffuse lighting from point light */
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

/* Clamps all color channels to the [0,255] range */
static t_color	clamp_color(t_color c)
{
	if (c.r < 0)
		c.r = 0;
	if (c.g < 0)
		c.g = 0;
	if (c.b < 0)
		c.b = 0;
	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	return (c);
}

/* Applies ambient and diffuse lighting to a hit */
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
	result.r = obj_color.r * (ambient * scene->ambient.color.r / 255.0
			+ diffuse);
	result.g = obj_color.g * (ambient * scene->ambient.color.g / 255.0
			+ diffuse);
	result.b = obj_color.b * (ambient * scene->ambient.color.b / 255.0
			+ diffuse);
	return (clamp_color(result));
}

/* Tests ray intersections and writes pixel color */
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
		img_pixel_put(scene, ray->pixel_x, ray->pixel_y, color);
		return (1);
	}
	img_pixel_put(scene, ray->pixel_x, ray->pixel_y, 0x000000);
	return (1);
}
