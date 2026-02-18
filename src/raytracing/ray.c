/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Resets all hit fields to their default values */
void	reset_hit(t_hit *hit)
{
	hit->inter = (t_vector){0.0, 0.0, 0.0};
	hit->delta = -1;
	hit->id = -1;
	hit->object_type = NONE;
	hit->object = NULL;
	hit->hit = FALSE;
}

/* Initializes ray origin, direction and hit data */
void	init_ray(t_ray *ray, t_vector origin, t_vector direction)
{
	ray->origin = origin;
	ray->direction = direction;
	reset_hit(&ray->hit);
}
