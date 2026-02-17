/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:06:11 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_vector	get_cap_center(t_cylinder *cyl, double sign)
{
	t_vector	cap;

	cap.x = cyl->center.x + cyl->axis.x * sign * cyl->height / 2;
	cap.y = cyl->center.y + cyl->axis.y * sign * cyl->height / 2;
	cap.z = cyl->center.z + cyl->axis.z * sign * cyl->height / 2;
	return (cap);
}

static double	hit_single_cap(t_cylinder *cyl, t_ray *ray, double sign)
{
	t_vector	cap;
	t_vector	oc;
	t_vector	diff;
	double		denom;
	double		t;

	cap = get_cap_center(cyl, sign);
	denom = scalar_product(ray->direction, cyl->axis);
	if (fabs(denom) < 1e-6)
		return (-1);
	oc.x = cap.x - ray->origin.x;
	oc.y = cap.y - ray->origin.y;
	oc.z = cap.z - ray->origin.z;
	t = scalar_product(oc, cyl->axis) / denom;
	if (t < 0.001)
		return (-1);
	diff = point_value(ray, t);
	diff.x -= cap.x;
	diff.y -= cap.y;
	diff.z -= cap.z;
	if (scalar_product(diff, diff) <= cyl->radius * cyl->radius)
		return (t);
	return (-1);
}

double	intersect_caps(t_cylinder *cyl, t_ray *ray)
{
	double	t_top;
	double	t_bot;

	t_top = hit_single_cap(cyl, ray, 1.0);
	t_bot = hit_single_cap(cyl, ray, -1.0);
	if (t_top > 0.001 && (t_bot < 0.001 || t_top < t_bot))
		return (t_top);
	if (t_bot > 0.001)
		return (t_bot);
	return (-1);
}
