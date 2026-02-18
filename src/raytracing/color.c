/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Converts a t_color to a packed 32-bit integer */
int	rgb_to_int(t_color color)
{
	return (((int)color.r << 16) | ((int)color.g << 8) | (int)color.b);
}

/* Writes a color value to the image buffer */
void	img_pixel_put(t_scene *scene, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = scene->img_addr + (y * scene->line_len + x * (scene->bpp / 8));
	*(unsigned int *)dst = color;
}
