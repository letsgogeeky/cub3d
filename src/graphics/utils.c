#include "cube.h"

void	clear_image(mlx_image_t *image, int width, int height)
{
    int	x;
    int	y;

    x = 0;
    y = 0;
    while (y < height)
    {
        while (x < width)
        {
            mlx_put_pixel(image, x, y, 0x00000000);
            x++;
        }
        x = 0;
        y++;
    }
}
