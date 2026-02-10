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

t_bool	is_normalized_vector(t_vector *vec)
{
	double	magnitude;

	magnitude = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
	if (magnitude < 0.99 || magnitude > 1.01)
	{
		return (FALSE);
	}
	return (TRUE);
}
