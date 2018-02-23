/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_detail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:11:21 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 10:29:46 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	get_type(char *str_obj)
{
		if (ft_strstr(str_obj, "PLA"))
			return (PLA);
		else if (ft_strstr(str_obj, "CYL"))
			return (CYL);
		else if (ft_strstr(str_obj, "CON"))
			return (CYL);
		else if (ft_strstr(str_obj, "LIG"))
			return (LIG);
		else
			return (ERROR);
}

t_vec	get_vec(char *str_obj, int *i_str)
{
	t_vec	vec;

	vec.x = (double)ft_atoi(str_obj + (*i_str));
	while (str_obj[(*i_str)] && ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	while (str_obj[(*i_str)] && !ft_isdigit(str_obj[(*i_str)]) &&
	str_obj[(*i_str)] != '-')
		(*i_str)++;
	vec.y = (double)ft_atoi(str_obj + (*i_str));
	while (str_obj[(*i_str)] && ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	while (str_obj[(*i_str)] && !ft_isdigit(str_obj[(*i_str)]) &&
	str_obj[(*i_str)] != '-')
		(*i_str)++;
	vec.z = (double)ft_atoi(str_obj + (*i_str));
	while (str_obj[(*i_str)] && ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	return (vec);
}

t_color	get_color(char *str_obj, int *i_str)
{
	t_color	color;

	color.r = (char)ft_atoi(str_obj + (*i_str));
	while (str_obj[(*i_str)] && ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	while (str_obj[(*i_str)] && !ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	color.g = (char)ft_atoi(str_obj + (*i_str));
	while (str_obj[(*i_str)] && ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	while (str_obj[(*i_str)] && !ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	color.b = (char)ft_atoi(str_obj + (*i_str));
	while (str_obj[(*i_str)] && ft_isdigit(str_obj[(*i_str)]))
		(*i_str)++;
	return (color);
}
