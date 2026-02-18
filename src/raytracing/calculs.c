/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Converts a radian angle value to degrees */
double	radian_to_degree(double rad)
{
	return (rad * (180.0 / M_PI));
}

/* Converts a degree angle value to radians */
double	degree_to_radian(double deg)
{
	return ((double)(deg * (M_PI / 180.0)));
}
