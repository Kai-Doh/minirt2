/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:42:53 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:06:11 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_hit
{
	t_bool		hit;
	double		delta;
	t_vector	inter;
	int			id;
	int			object_type;
	void		*object;
}	t_hit;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_hit		hit;
	int			pixel_x;
	int			pixel_y;
	t_color		color;
}	t_ray;

typedef struct s_base_world
{
	t_vector	forward;
	t_vector	right;
	t_vector	up;
}	t_base_world;

typedef struct s_camera
{
	t_vector	position;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	double		fov;
	double		d;
}	t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_vector	position;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_viewport
{
	double	width;
	double	height;
	double	px_x;
	double	px_y;
}	t_viewport;

typedef struct s_sphere
{
	int			id;
	t_vector	center;
	double		radius;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	int			id;
	t_vector	point;
	t_vector	normal;
	t_color		color;
	double		d;
}	t_plane;

typedef struct s_cylinder
{
	int			id;
	t_vector	center;
	t_vector	axis;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_scene
{
	t_camera		camera;
	t_base_world	base_world;
	t_ambient		ambient;
	t_light			light;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	t_viewport		viewport;
	int				ambient_count;
	int				camera_count;
	int				light_count;
	int				sphere_count;
	int				plane_count;
	int				cylinder_count;
	void			*mlx;
	void			*mlx_win;
}	t_scene;

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_scene	scene;
}	t_data;

#endif
