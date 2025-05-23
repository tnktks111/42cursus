#ifndef FDF_H
#define FDF_H

#include "mlx.h"
#include "get_next_line.h"
#include "libft_for_fdf.h"
#include <math.h>
#include <fcntl.h>
#include <stdint.h>

#define W_WIDTH 800
#define W_HEIGHT 600
#define MOUSE_CLICK_LEFT 1
#define MOUSE_CLICK_RIGHT 2
#define MOUSE_CLiCK_MIDDLE 3
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DOWN 5
#define SPACE 32
#define ESCAPE 53
#define K_R 15
#define LEFT_ARROW 123
#define RIGHT_ARROW 124
#define DOWN_ARROW 125
#define UP_ARROW 126

typedef enum e_bool
{
    False, True
} t_bool;

typedef struct s_quaternion
{
    double w;
    double x;
    double y;
    double z;
} t_quaternion;

typedef struct s_mappoint
{
    t_quaternion a;
    t_quaternion va;
    uint32_t color;
} t_mappoint;


typedef struct s_env
{
    t_mappoint **map;
    int m_width;
    int m_height;
    int w_width;
    int w_height;
    double min_x;
    double min_y;
    double virtual_square;
    double scaling;
    double offset_x;
    double offset_y;
    double user_offset_x;
    double user_offset_y;
    t_quaternion v_start;
    t_quaternion v_curr;
    t_quaternion rot;
    t_bool is_dragging;
    void *mlx_ptr;
    void *win_ptr;
    void *img;
    char *addr;
    int *elevation_map;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_env;

int parser(int argc, char *argv, t_env *env);
int map_parser(int fd, t_env *env);
void element_parser(char *str, long *res);

int	ft_count(char const *s, char c);
int line_counter(int fd, t_env *env);
int count_items(char **datas);
void	**free_splitted_datas(char **words);

void calc_mapsize(t_env *env);
void recalc_mapsize(t_env *env);

void plot(t_env *env, int x, int y, int z, int rgb, double brightness);
void xiaolin_wu(t_env *env, t_mappoint p0, t_mappoint p1);
void line_drawer(t_env *env);
void vertical_line_drawer(t_env *env);
void horizontal_line_drawer(t_env *env);

void hook_handler(t_env *env);
int key_button_press(int key, void *param_env);
int handle_button_press(int button, int x, int y, void *param_env);
int handle_mouse_motion(int x, int y, void *param_env);
int handle_button_release(int button, int x, int y, void *param_env);

t_quaternion map_mouse_to_sphere(int x, int y, t_env *env);
t_quaternion vector_cross_product(t_quaternion p, t_quaternion q);
double vector_inner_product(t_quaternion p, t_quaternion q);

int translate_view(int key, t_env *env);

void redraw_line_after_rotation(t_quaternion rot, t_env *env);
void redraw_line_after_translation(t_env *env);
void redraw_line_after_zoom(t_env *env);
void reset_view(t_env *env);

t_quaternion set_quaternion(double w, double x, double y, double z);
double norm_of_quaternion(t_quaternion q);
t_quaternion quaternion_conjugate(t_quaternion q);
t_quaternion quaternion_product(t_quaternion q, t_quaternion p);
void quaternion_product_in_place(t_quaternion *p, t_quaternion rot);
t_quaternion rot_isometric(t_quaternion p, t_env *env);

t_quaternion normalize_quaternion(t_quaternion q);
t_quaternion gen_rot_quaternion(t_quaternion axis, double angle);
void update_rot_quaternion(t_quaternion rot, t_env *env);
void rot_based_on_quaternion(t_quaternion p, t_quaternion *p_prime, t_env *env);

int	create_rgb(int r, int g, int b);
int	get_r(int rgb);
int	get_g(int rgb);
int	get_b(int rgb);
int add_shade(int rgb, double shade_factor);
int get_opposite(int rgb);
int interpolate_color(int c_start, int c_end, double t);

void free_map_partial(t_env *env, int allocated);
void free_map(t_env *env);
void close_window(t_env *env);

#endif