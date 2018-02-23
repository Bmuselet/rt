/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs_and_cam.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:46:39 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/23 10:08:08 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj	get_one_obj(char *str_obj)
{
	t_obj	obj;
	int		i_str;

	obj.type = get_type(str_obj);
	i_str = 0;
	while (!ft_isdigit(str_obj[i_str]))
		i_str++;
	obj.pos = get_vec(str_obj, &i_str);
	while (!ft_isdigit(str_obj[i_str]))
		i_str++;
	obj.rad = (double)ft_atoi(str_obj + i_str);
	while (!ft_isdigit(str_obj[i_str]))
		i_str++;
	obj.color = get_color(str_obj, &i_str);
	while (!ft_isdigit(str_obj[i_str]))
		i_str++;
	obj.rot = get_vec(str_obj, &i_str);
	while (!ft_isdigit(str_obj[i_str]))
		i_str++;
	obj.trans = get_vec(str_obj, &i_str);
	return (obj);
}

static void	get_objs(t_list **line_lst, t_env *e)
{
	char	*str_obj;
	t_obj	obj;

	while (*line_lst)
	{
		str_obj = NULL;
		while (!str_obj)
		{
			str_obj = ft_strstr((*line_lst)->content, "SPH");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "PLA");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "CYL");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "CON");
			if (!str_obj)
				str_obj = ft_strstr((*line_lst)->content, "LIG");
			*line_lst = (*line_lst)->next;
		}
		obj = get_one_obj(str_obj);
		ft_lstadd(&(e->objs), ft_lstnew(&obj, sizeof(t_obj)));
	}
}

static void	get_cam(t_list **line_lst, t_env *e)
{
	char	*str_cam;
	int		i_str;

	while (!(str_cam = ft_strstr((*line_lst)->content, "CAM")))
		*line_lst = (*line_lst)->next;
	i_str = 0;
	while (!ft_isdigit(str_cam[i_str]))
		i_str++;
	e->cam.pos.x = ft_atoi(str_cam + i_str);
	while (ft_isspace(str_cam[i_str]))
		i_str++;
	e->cam.pos.y = ft_atoi(str_cam + i_str);
	while (ft_isspace(str_cam[i_str]))
		i_str++;
	e->cam.pos.z = ft_atoi(str_cam + i_str);
	while (ft_isspace(str_cam[i_str]))
		i_str++;
	e->cam.dir.x = ft_atoi(str_cam + i_str);
	while (ft_isspace(str_cam[i_str]))
		i_str++;
	e->cam.dir.y = ft_atoi(str_cam + i_str);
	while (ft_isspace(str_cam[i_str]))
		i_str++;
	e->cam.dir.z = ft_atoi(str_cam + i_str);
}

static void	ft_delstr(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

void	get_objs_and_cam(t_env *e, char *path_file)
{
	t_list	*line_lst;

	read_to_lst(path_file, &line_lst);
	get_cam(&line_lst, e);
	get_objs(&line_lst, e);
	ft_lstdel(&line_lst, &ft_delstr);
}
