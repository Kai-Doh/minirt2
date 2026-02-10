/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	init_viewport(t_scene *scene)
{
	double	ratio_asp;
	double	fov_rad;

	scene->camera.d = 1.0;
	fov_rad = degree_to_radian(scene->camera.fov);
	ratio_asp = (double)WIDTH / (double)HEIGHT;
	scene->viewport.width = 2.0 * scene->camera.d * tan(fov_rad * 0.5);
	scene->viewport.height = scene->viewport.width / ratio_asp;
	scene->viewport.px_x = scene->viewport.width / (double)WIDTH;
	scene->viewport.px_y = scene->viewport.height / (double)HEIGHT;
	return (1);
}
