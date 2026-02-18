/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Returns the dot product of two vectors */
double	scalar_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/* Returns the cross product of two vectors */
t_vector	vector_product(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}

/* Returns the Euclidean length of a vector */
double	vector_norm(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/* Returns vector scaled by a scalar factor */
t_vector	vector_scale(t_vector v, double n)
{
	t_vector	result;

	result.x = v.x * n;
	result.y = v.y * n;
	result.z = v.z * n;
	return (result);
}

/* Returns a unit-length version of a vector */
t_vector	vector_normalize(t_vector v)
{
	double		norm_sqrt;
	t_vector	result;
	double		inv_l;

	norm_sqrt = v.x * v.x + v.y * v.y + v.z * v.z;
	if (norm_sqrt < 1e-24)
		return ((t_vector){0, 0, 0});
	inv_l = 1.0 / sqrt(norm_sqrt);
	result.x = v.x * inv_l;
	result.y = v.y * inv_l;
	result.z = v.z * inv_l;
	return (result);
}
