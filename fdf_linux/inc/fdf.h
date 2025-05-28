/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:12:35 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 21:13:01 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "libft_for_fdf.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>

# define START_FILE_PATH "xpm/start_display.xpm"
# define XPM_FILE_PATH "xpm/menu.xpm"

# define FORMAT_ERR -4

# define BACKGROUND 0x4D5F8D
# define W_WIDTH 800
# define W_HEIGHT 600
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define SPACE 32
# define ESCAPE 65307
# define ENTER 65293
# define TAB 65289
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_R 114
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define UP_ARROW 65362

typedef enum e_bool
{
	False,
	True
}					t_bool;

typedef enum e_mode
{
	Iso,
	XY,
	YZ,
	ZX
}					t_mode;

typedef struct s_data
{
	char			*line;
	char			**elements;
}					t_data;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct s_quaternion
{
	double			w;
	double			x;
	double			y;
	double			z;
}					t_quaternion;

typedef struct s_mappoint
{
	t_quaternion	a;
	t_quaternion	va;
	uint32_t		color;
}					t_mappoint;

typedef struct s_draw_var
{
	t_bool			reversed;
	t_mappoint		start;
	t_mappoint		end;
	double			dx;
	double			dy;
	double			grad;
	int				x_pxl1;
	int				y_pxl1;
	int				x_pxl2;
	int				y_pxl2;
	double			intery;
}					t_draw_var;

typedef struct s_env
{
	t_mappoint		**map;
	int				m_width;
	int				m_height;
	int				w_width;
	int				w_height;
	double			min_x;
	double			min_y;
	double			virtual_square;
	double			scaling;
	double			offset_x;
	double			offset_y;
	double			user_offset_x;
	double			user_offset_y;
	t_quaternion	v_start;
	t_quaternion	v_curr;
	t_quaternion	rot;
	t_bool			is_dragging;
	t_bool			start;
	t_bool			display_menu;
	t_mode			mode;
	unsigned char	errno;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*addr;
	void			*start_xpm;
	void			*menu_xpm;
	int				start_img_height;
	int				start_img_width;
	int				menu_img_height;
	int				menu_img_width;
	int				*elevation_map;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_env;

// 01_parser.c
int					parser(int argc, char *argv, t_env *env);
int					map_converter(int row, t_data datas, t_env *env);
int					map_parser(int fd, t_env *env);
void				element_parser(char *str, long *res);

// 02_parser_helper.c
int					ft_count(char const *s, char c);
int					line_counter(int fd, t_env *env);
int					count_items(char **datas);
void				**free_splitted_datas(char **words);

// 03_calculator.c
t_bool				is_in_screen(t_mappoint p0, t_mappoint p1, t_bool reversed);
void				calc_mapsize(t_env *env, double vessel[3][2]);
void				adjust_offset(t_env *env);
void				readjust_offset(t_env *env);

// 04_xiaolin_wu.c
void				plot(t_env *env, t_point p, double brightness,
						t_bool reversed);
t_point				gen_point(int x, int y, int z, int color);
void				plot_edge(t_env *env, t_draw_var *info, t_mappoint p,
						t_bool is_start);
void				plot_loop(t_env *env, t_draw_var *info);
void				xiaolin_wu(t_env *env, t_mappoint p0, t_mappoint p1,
						t_bool reversed);

// 05_line_drawer.c
void				fill_background(t_env *env, int color);
void				line_drawer(t_env *env);
void				vertical_line_drawer(t_env *env);
void				horizontal_line_drawer(t_env *env);

// 06_hook_handler.c
void				hook_handler(t_env *env);
int					key_button_press(int key, void *param_env);
int					handle_button_press(int button, int x, int y,
						void *param_env);
int					handle_mouse_motion(int x, int y, void *param_env);
int					handle_button_release(int button, int x, int y,
						void *param_env);

// 07_menu.c
void				switch_menu_frag(t_env *env);

// 08_mouse.c
t_quaternion		map_mouse_to_sphere(int x, int y, t_env *env);
t_quaternion		vector_cross_product(t_quaternion p, t_quaternion q);
double				vector_inner_product(t_quaternion p, t_quaternion q);

// 09_translation.c
int					translate_view(int key, t_env *env);

// 10_redraw_and_reset.c
void				redraw_line_after_rotation(t_quaternion rot, t_env *env);
void				redraw_line_after_translation(t_env *env);
void				redraw_line_after_tab(t_env *env);
void				redraw_line_after_zoom(t_env *env);
void				reset_view(t_env *env);

// 11_switch_view.c
void				switch_view(t_env *env);

// 12_quaternion_utils.c
t_quaternion		set_quaternion(double w, double x, double y, double z);
double				norm_of_quaternion(t_quaternion q);
t_quaternion		quaternion_conjugate(t_quaternion q);
t_quaternion		quaternion_product(t_quaternion q, t_quaternion p);
void				quaternion_product_in_place(t_quaternion *p,
						t_quaternion rot);

// 13_quaternion_utils2.c
t_quaternion		normalize_quaternion(t_quaternion q);
t_quaternion		gen_rot_quaternion(t_quaternion axis, double angle);
void				update_rot_quaternion(t_quaternion rot, t_env *env);
void				rot_based_on_quaternion(t_quaternion p,
						t_quaternion *p_prime, t_env *env);

// 14_quaternion_utils3.c
t_quaternion		rot_isometric(t_quaternion p, t_env *env);
t_quaternion		rot_yz(t_quaternion p, t_env *env);
t_quaternion		rot_zx(t_quaternion p, t_env *env);
t_quaternion		rot_based_on_view_mode(t_quaternion p, t_env *env);

// 15_color.c
int					create_rgb(int r, int g, int b);
int					get_r(int rgb);
int					get_g(int rgb);
int					get_b(int rgb);

// 16_color2.c
int					add_shade(int rgb, double shade_factor);
int					get_opposite(int rgb);
int					interpolate_color(int c_start, int c_end, double t);

// 17_init.c
void				init_environment(t_env *env);

// 18_error.c
int					put_errmsg(char *err_msg);

// 19_free.c
void				free_map_partial(t_env *env, int allocated);
void				free_map(t_env *env);
int					close_window(t_env *env);

// 20_utils.c
void				remove_end_n(char *str);

#endif