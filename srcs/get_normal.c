/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:11:09 by bmuselet          #+#    #+#             */
/*   Updated: 2018/02/28 17:45:31 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	if (ray.hit_obj->type == CON)
		normal = vector_double_product(normal,
			powf(cosf(ray.hit_obj->rad * (M_PI * 180.0f)), 2));
	return (normal);
}

t_vec	get_normal(t_env *e, t_vec hit_point, t_ray ray)
{
	t_vec normal;

	if (ray.hit_obj->type == PLA)
		normal = ((t_obj*)e->objs->content)->dir;
	else if (ray.hit_obj->type == SPH)
		normal = vector_substraction(hit_point, ray.hit_pos);
	else if (ray.hit_obj->type == CON || ray.hit_obj->type == CYL)
		normal = get_normal_2(hit_point, ray);
	else
		normal = (t_vec){0, 0, 0};
	normal = vector_normalize(normal);
	return (normal);
}
