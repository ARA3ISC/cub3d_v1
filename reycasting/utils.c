
#include "../cub3d.h"

int rgb_to_hex(int red, int green, int blue)
{
    return (red << 16) | (green << 8) | blue;
}