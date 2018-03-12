/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmuselet <bmuselet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:48:33 by bmuselet          #+#    #+#             */
/*   Updated: 2018/03/12 11:18:29 by bmuselet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_H

# define RT_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h> //<- A SUPPRIMER

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define EXIT_PRESS 17
# define EXIT_PRESS_MASK (1L << 17)
# define KEY_PRESS_MASK (1L << 6)
# define MOUSE_PRESS_MASK (1L << 2)
# define MOUSE_MOVE_MASK (1L << 6)

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_W 13
# define KEY_R 15
# define KEY_N 45
# define KEY_M 46
# define KEY_SPACE 49
# define KEY_ECHAP 53
# define KEYPAD_RIGHT 124
# define KEYPAD_LEFT 123
# define KEYPAD_UP 126
# define KEYPAD_DOWN 125

# define INVALID_FILE_DESCRIPTION 0
# define INVALID_FILE 1
# define INVALID_ARG 2

# define ON 1
# define OFF 0

# define FOV 2

# define ERROR -1
# define SPH 0
# define PLA 1
# define CYL 2
# define CON 3
# define LIG 4

# define ROT_SPEED 0.1
# define MOVE_SPEED 10

# define INFINITE 1000000000

# define NB_THREADS 1

# define TRUE 1
# define FALSE 0

# define NB_MIRRORING 0

typedef struct		s_obj
{
	char			type;
	t_vec			pos;
	t_vec			dir;
	double			rad;
	t_color			color;
	t_vec			rot;
	t_vec			trans;
	char			mirror;
}					t_obj;

typedef struct		s_ray
{
	t_vec 			pos;
	t_vec			dir;
	double			length;
	double			disc;
	t_vec			normal;
	t_obj			*hit_obj;
	t_vec			hit_pos;
	t_vec			hit_dir;
}					t_ray;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				size_x;
	int				size_y;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_cam
{
	double			dist;
	double			focal;
	double			lens_rad;
	double			zoom;
	int				num_samples;
	int 			antialiasing;
	int				cel_shading;
	int				sepia;
	int				bnw;
	int				reverse;
	t_vec			pos;
	t_vec			dir;
	t_vec			right;
	t_vec			up;
	t_vec			forward;
	t_obj			*prev_ray_obj;
	t_point			samp;
}					t_cam;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				y_start;
	int				y_end;
	t_cam			cam;
	t_list			*objs;
	t_list			*lights;
}					t_env;

void				ft_delstr(void *content, size_t content_size);

t_img				new_image(void *mlx, int img_size_x, int img_size_y);
void				del_image(void *mlx, t_img *img);
void				put_pixel_to_image(t_img *img, int x, int y, t_color color);

void				set_cam_coordinates(t_env *e);
t_vec				ray_dir_cal(t_env *e, double i, double j, int s);

char				get_type(char *str_obj);
t_vec				get_vec(char *str_obj, int *i_str);
t_color				get_color(char *str_obj, int *i_str);
int					get_nbr(char *str_obj, int *i_str);
void				get_objs_and_cam(t_env *e, char *path_file);
int					check_inter_objects(t_env *e, t_ray *ray);

double				cone_inter(t_env *e, t_ray *ray);
double				plan_inter(t_env *e, t_ray *ray);
double				cylindre_inter(t_env *e, t_ray *ray);
double				sphere_inter(t_env *e, t_ray *ray);
void				draw(t_env *e);
void				ray_mirror(t_env *e, t_ray *ray, int nb_rebond);
int					key_hook(int keycode, t_env *e);
int					button_exit(int keycode, t_env *e);
t_color 			light_calc(t_env *e, t_ray ray);
void				transformations(t_obj *obj);
t_vec				get_normal(t_vec hit_point, t_ray ray);

// PARTIE BENJAMIN //
void				multi_thread(t_env *e);
double				cel_shading(t_env *e, double d);
t_color				cel_shading_shape(t_env *e, t_ray ray, t_color color);
t_color				damier_texture(t_vec hit_point);
void				turbulence(t_vec hit_point, t_color *color, double size);
void				marble_texture(t_vec hit_point, t_color *color);
void				wood_texture(t_vec hit_point, t_color *color);
void 				perlin_color(t_vec hit_point, t_color *color);
t_vec				bump_mapping(t_vec hit_point, t_vec normal);
void				blend_color(t_env *e, t_color *color, int x, int y);
void				antialiasing(t_env *e, t_vec compteur, t_color *color);
t_color				search_color(void *e, int x, int y, int s);
t_color 			filter_color(t_env *e, t_color color, t_ray ray);
int					key_filter(int keycode, t_env *e);

double				noise(double x, double y, double z);
double				fade(double t);
double				lerp(double t, double a, double b);
double				grad(int hash, double x, double y, double z);
/////////////////////

#endif
