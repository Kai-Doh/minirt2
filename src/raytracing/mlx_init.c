/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	create_image(t_scene *scene)
{
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->img)
		return (0);
	scene->img_addr = mlx_get_data_addr(scene->img,
			&scene->bpp, &scene->line_len, &scene->endian);
	if (!scene->img_addr)
		return (0);
	return (1);
}

#ifdef __linux__

void	mlx_cleanup(t_scene *scene)
{
	if (scene->img)
		mlx_destroy_image(scene->mlx, scene->img);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
}

int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (printf("Error\nImpossible to init mlx\n"), 0);
	scene->mlx_win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!scene->mlx_win)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
		return (printf("Error\nImpossible to create window\n"), 0);
	}
	if (!create_image(scene))
	{
		mlx_destroy_window(scene->mlx, scene->mlx_win);
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
		return (printf("Error\nImpossible to create image\n"), 0);
	}
	return (1);
}

#else

void	mlx_cleanup(t_scene *scene)
{
	if (scene->img)
		mlx_destroy_image(scene->mlx, scene->img);
	if (scene->mlx)
		free(scene->mlx);
}

int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (printf("Error\nImpossible to init mlx\n"), 0);
	scene->mlx_win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!scene->mlx_win)
	{
		free(scene->mlx);
		return (printf("Error\nImpossible to create window\n"), 0);
	}
	if (!create_image(scene))
	{
		mlx_destroy_window(scene->mlx, scene->mlx_win);
		free(scene->mlx);
		return (printf("Error\nImpossible to create image\n"), 0);
	}
	return (1);
}

#endif
