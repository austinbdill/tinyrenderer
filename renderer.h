#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "tgaimage.h"
#include "linalg.h"


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Vec3f *pts, float *z_buffer, TGAImage &image, TGAColor color);

TGAImage render_wireframe(const char *filename, TGAColor color, const int width, const int height);

TGAImage render_mesh(const char *filename, Vec3f light_direction, TGAColor color, const int width, const int height);

Vec3f barycentric_coordinates(Vec3f a, Vec3f b, Vec3f c, Vec2i p);

Vec3f world2screen(Vec3f v, int width, int height);

#endif