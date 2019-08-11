#include "alt.h"

#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define tex_len 8

/* TEST */
void init_textures(t_scene *scene)
{
  int x;
  int y;
  int len;

  len = 0;
  scene->textures = (Uint32 **)malloc(sizeof(Uint32 *) * tex_len);
  while (len < tex_len)
  {
    scene->textures[len] = (Uint32 *)malloc(sizeof(Uint32) * TEX_WIDTH * TEX_HEIGHT);
    len++;
  }

  x = 0;
  while (x < TEX_WIDTH)
  {
    y = 0;
    while (y < TEX_HEIGHT)
    {
      Uint32 xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
      Uint32 ycolor = y * 256 / TEX_HEIGHT;
      Uint32 xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
      scene->textures[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y);
      scene->textures[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
      scene->textures[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;
      scene->textures[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
      scene->textures[4][TEX_WIDTH * y + x] = 256 * xorcolor;
      scene->textures[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);
      scene->textures[6][TEX_WIDTH * y + x] = 65536 * ycolor;
      scene->textures[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;
      y++;
    }
    x++;
  }
  scene->tex_width = TEX_WIDTH;
  scene->tex_height = TEX_HEIGHT;
}