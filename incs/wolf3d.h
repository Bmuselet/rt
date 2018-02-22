/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:50:24 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/22 12:17:11 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

# define WIN_SIZE_X 1080
# define WIN_SIZE_Y 720

# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define EXIT_PRESS 17
# define EXIT_PRESS_MASK (1L<<17)
# define KEY_PRESS_MASK (1L << 6)
# define MOUSE_PRESS_MASK (1L << 2)
# define MOUSE_MOVE_MASK (1L << 6)

# define KEY_ECHAP 53
# define KEYPAD_RIGHT 124
# define KEYPAD_LEFT 123
# define KEYPAD_UP 126
# define KEYPAD_DOWN 125

# define INVALID_FILE_DESCRIPTION 0
# define INVALID_FILE 1
# define INVALID_ARG 2

# define SPHERE 0

typedef	struct	s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct	s_color
{
	char	r;
	char	g;
	char	b;
}				t_color;

typedef struct	s_obj
{
	char	type;
	t_vec	pos;
	double	ray;
	t_color	color;
	t_vec	rot;
	t_vec	trans;
}

typedef struct	s_img
{
	void	*img;
	char	*data;
	int		size_x;
	int		size_y;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_cam
{
	t_vec	pos;
	t_vec	dir;
}				t_cam;

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_cam			cam;
	t_list			*objs;
}				t_env;

#endif
