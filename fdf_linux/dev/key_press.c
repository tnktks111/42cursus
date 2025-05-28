#include "../inc/mlx.h"
#include <stdio.h>

//cc -L . -lmlx -framework OpenGL -framework Appkit ./libmlx.dylib dev/key_press.c -o key_test

int key_press_hook(int keycode, void *param)
{
    (void)param;
    printf("Key pressed: %d\n", keycode);
    if (keycode == 53)
        printf("ESC key (macOS) pressed!\n");
    else if (keycode == 65307)
        printf("ESC key (Linux) pressed!\n");
    return (0);
}

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return (1);
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Key Test");
    if (!win_ptr)
        return (1);

    mlx_key_hook(win_ptr, key_press_hook, NULL);

    mlx_loop(mlx_ptr);
    return (0);
}