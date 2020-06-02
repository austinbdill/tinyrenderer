#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "tgaimage.h"
#include "linalg.h"


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Vec2i *pts, TGAImage &image, TGAColor color);

#endif