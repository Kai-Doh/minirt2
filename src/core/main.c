/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;

	if (!arg_check(ac, av))
		return (1);
	init_scene(&scene);
	if (!parse_scene(av[1], &scene))
	{
		cleanup_scene(&scene);
		return (1);
	}
	if (!validate_scene(&scene))
	{
		cleanup_scene(&scene);
		return (1);
	}
	print_scene_summary(&scene);
	if (!raytracer(&scene))
	{
		cleanup_scene(&scene);
		return (1);
	}
	cleanup_scene(&scene);
	return (0);
}
