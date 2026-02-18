/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <ktiomico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:43:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/11/24 16:31:37 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* ============ CORE ============ */
t_bool		arg_check(int ac, char **av);
void		print_scene_summary(t_scene *scene);

/* ============ VALIDATION ============ */
void		init_scene(t_scene *scene);
void		cleanup_scene(t_scene *scene);
t_bool		validate_scene(t_scene *scene);
t_bool		is_normalized_vector(t_vector *vec);

/* ============ PARSING ============ */
t_bool		parse_scene(char *filename, t_scene *scene);
t_bool		parse_line(char *line, t_scene *scene);
t_bool		process_lines(int fd, t_scene *scene);
t_bool		identify_element(char **tokens, char *line, t_scene *scene);
t_bool		parse_ambient(char **tokens, t_scene *scene);
t_bool		parse_camera(char **tokens, t_scene *scene);
t_bool		parse_light(char **tokens, t_scene *scene);
t_bool		parse_sphere(char **tokens, t_scene *scene);
t_bool		parse_plane(char **tokens, t_scene *scene);
t_bool		parse_cylinder(char **tokens, t_scene *scene);
t_bool		check_cylinder_token_count(char **tokens);
t_bool		parse_cylinder_geometry(char **tokens, t_cylinder *cyl);
t_cylinder	*allocate_cylinder(t_scene *scene);

/* ============ UTILS ============ */
t_bool		is_valid_double(char *str);
double		parse_double(char *str);
void		free_split(char **split);

/* ============ MATH ============ */
t_bool		parse_vector(char *str, t_vector *vec);
t_bool		parse_color(char *str, t_color *color);

/* ============ RAYTRACING ============ */
double		radian_to_degree(double rad);
double		degree_to_radian(double deg);
int			ray_intersec(t_ray *ray, t_scene *scene);
t_vector	point_value(t_ray *ray, double t);
void		get_nearest_point(t_ray *ray, double *closest_t);
int			intersec_spheres(t_ray *ray, t_scene *scene);
int			intersec_planes(t_ray *ray, t_scene *scene);
int			intersec_cylinders(t_ray *ray, t_scene *scene);
double		intersect_caps(t_cylinder *cyl, t_ray *ray);
int			init_mlx(t_scene *scene);
void		mlx_cleanup(t_scene *scene);
void		img_pixel_put(t_scene *scene, int x, int y, int color);
int			close_window(t_scene *scene);
int			handle_key(int keycode, t_scene *scene);
int			handle_expose(t_scene *scene);
t_vector	change_base_ray(t_vector v, t_scene *scene);
int			render_pixel_step(t_scene *scene);
int			raytracer(t_scene *scene);
int			init_viewport(t_scene *scene);
double		scalar_product(t_vector v1, t_vector v2);
t_vector	vector_product(t_vector v1, t_vector v2);
double		vector_norm(t_vector v);
t_vector	vector_scale(t_vector v, double n);
t_vector	vector_normalize(t_vector v);
int			make_base_cam(t_scene *scene);
int			make_orientation_cam(t_scene *scene);
int			rgb_to_int(t_color color);
void		init_ray(t_ray *ray, t_vector origin, t_vector direction);
void		reset_hit(t_hit *hit);
int			is_perpendicular(t_vector v1, t_vector v2);
double		ft_sqr(double x);
t_vector	get_normal(t_ray *ray, t_scene *scene);
int			is_in_shadow(t_vector point, t_scene *scene, t_hit *hit);
int			check_shadow_sphere(t_ray *sh, t_scene *scene, double light_d);
int			check_shadow_plane(t_ray *shadow, t_scene *scene, double light_d);
int			cyl_height_check(t_ray *sh, t_cylinder *cyl, double t);
void		calc_cyl_abc(t_ray *sh, t_cylinder *cyl, double *abc);

#endif
