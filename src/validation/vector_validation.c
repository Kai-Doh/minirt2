/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/09/09 16:30:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Validates and normalizes a direction vector */
t_bool	is_normalized_vector(t_vector *vec)
{
	double	magnitude;

	if (vec->x < -1 || vec->x > 1 || vec->y < -1 || vec->y > 1
		|| vec->z < -1 || vec->z > 1)
		return (FALSE);
	magnitude = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
	if (magnitude < 1e-10)
		return (FALSE);
	*vec = vector_normalize(*vec);
	return (TRUE);
}
