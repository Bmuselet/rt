/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:20:24 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/26 14:16:46 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int  search_shadow(t_env *e, t_vec hit_point, t_vec light_dir)
{
  t_ray		ray;
	double		light_dist;

  ray.dir = vector_substraction(((t_obj*)e->lights->content)->pos, hit_point);
  light_dist = sqrt(vector_dot_product(light_dir, light_dir));
	vector_normalize(ray.dir);
  ray_loop(e, ray);
	if (e->ray.length <= light_dist)
		return (1);
  return (0);
}

t_color	light_calc(t_env *e, t_color color)
{
	t_vec	hit_point;
	t_vec	light_dir;
	t_vec	normale;
	double	d;

	hit_point = vector_addition(e->cam.pos,
			vector_double_product(e->ray.dir, e->ray.length));
	light_dir = vector_substraction(((t_obj*)e->lights->content)->
			pos, hit_point);
	light_dir = vector_normalize(light_dir);
	normale = vector_substraction(hit_point, e->ray.hit_pos);
	normale = vector_normalize(normale);
	d = ft_clamp(vector_dot_product(light_dir, normale), 0.0, 1.0);
//  if (search_shadow(e, hit_point, light_dir) == 1)
//    return ((t_color){255, 255, 255});
	color = e->ray.hit_color;
	color = color_mix(e->ray.hit_color, ((t_obj*)e->lights->content)->color);
	color = color_double_product(color, ((t_obj*)e->lights->content)->rad);
	color = color_double_product(color, d);
	return (color);
}
