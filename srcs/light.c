/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/27 17:56:33 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
static int  inter_shadow(t_env *e, t_vec hit_point, t_vec light_dir)
{
	double	light_dist;
	double	ray_length;
	t_list *tmp;

	light_dist = sqrt(vector_dot_product(light_dir, light_dir));
	light_dir = vector_double_product(light_dir, -1);
	//light_dir =  vector_normalize(light_dir);
	ray_length = 1000000000;
	tmp = e->objs;
	while (e->objs != NULL)
	{
		if (((t_obj*)e->objs->content)->type == SPH)
			ray_length = sphere_inter(e, hit_point, ((t_obj*)e->lights->content)->
					pos);
		if (((t_obj*)e->objs->content)->type == CYL)
			ray_length = cylindre_inter(e, hit_point, light_dir);
		if (((t_obj*)e->objs->content)->type == CON)
			ray_length = cone_inter(e, hit_point, light_dir);
		if (((t_obj*)e->objs->content)->type == PLA)
			ray_length = plan_inter(e, hit_point, light_dir);
		if (ray_length < light_dist)
			return (1);
		e->objs = e->objs->next;
	}
	e->objs = tmp;
	return (0);
}
*/

static t_vec	get_normal_2(t_vec hit_point, t_ray ray)
{
	t_vec tmp;
	t_vec tmp2;
	t_vec normal;

	vector_normalize(ray.hit_dir);
	tmp = vector_substraction(hit_point, ray.hit_pos);
	tmp2 = vector_double_product(ray.hit_dir,
	vector_dot_product(ray.hit_dir, tmp));
	normal = (t_vec){2 * (tmp.x - tmp2.x),
		2 * (tmp.y - tmp2.y), 2 * (tmp.z - tmp2.z)};
	if (ray.hit_type == CON)
		normal = vector_double_product(normal,
			powf(cosf(ray.hit_rad * (M_PI * 180.0f)), 2));
	return (normal);
}

static t_vec	get_normal(t_env *e, t_vec hit_point, t_ray ray)
{
	t_vec normal;

	if (ray.hit_type == PLA)
		normal = ((t_obj*)e->objs->content)->dir;
	if (ray.hit_type == SPH)
		normal = vector_substraction(hit_point, ray.hit_pos);
	else if (ray.hit_type == CON || ray.hit_type == CYL)
		normal = get_normal_2(hit_point, ray);
	else
		normal = (t_vec){0, 0, 0};
	normal = vector_normalize(normal);
	return (normal);
}

t_color			light_calc(t_env *e, t_ray ray)
{
	t_color	color;
	t_vec	hit_point;
	t_vec	light_dir;
	t_vec	normal;
	double	d;

	hit_point = vector_addition(e->cam.pos,
			vector_double_product(ray.dir, ray.length));
	light_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, hit_point);
	light_dir = vector_normalize(light_dir);
	normal = get_normal(e, hit_point, ray);
	d = ft_clamp(vector_dot_product(normal, light_dir), 0.0, 1.0);
	color = color_double_product(((t_obj*)e->lights->content)->color,
		((t_obj*)e->lights->content)->rad);
	color = color_mix(ray.hit_color, color);
	color = color_double_product(color, d);
	//if (inter_shadow(e, hit_point, light_dir) == 1)
	//		return ((t_color){0, 0, 0});
	return (color);
}
