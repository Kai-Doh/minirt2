/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Routes token to the appropriate parser function */
t_bool	identify_element(char **tokens, char *line, t_scene *scene)
{
	(void)line;
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		return (parse_ambient(tokens, scene));
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		return (parse_camera(tokens, scene));
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		return (parse_light(tokens, scene));
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		return (parse_sphere(tokens, scene));
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		return (parse_plane(tokens, scene));
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		return (parse_cylinder(tokens, scene));
	else
	{
		printf("Error\nUnknown element: %s\n", tokens[0]);
		return (FALSE);
	}
}

/* Splits a scene file line and dispatches to parser */
t_bool	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	t_bool	result;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		if (tokens)
			free_split(tokens);
		return (FALSE);
	}
	result = identify_element(tokens, line, scene);
	free_split(tokens);
	return (result);
}

/* Reads and parses all non-empty lines from file */
t_bool	process_lines(int fd, t_scene *scene)
{
	char	*line;
	int		line_num;

	line_num = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) > 1 && line[0] != '\n' && line[0] != '#')
		{
			if (!parse_line(line, scene))
			{
				printf("Error\nParsing line %d: %s\n", line_num, line);
				free(line);
				return (FALSE);
			}
		}
		free(line);
		line = get_next_line(fd);
		line_num++;
	}
	return (TRUE);
}

/* Opens scene file and processes all its lines */
t_bool	parse_scene(char *filename, t_scene *scene)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file '%s'\n", filename);
		return (FALSE);
	}
	if (!process_lines(fd, scene))
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
