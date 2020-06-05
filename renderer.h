#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "tgaimage.h"
#include "linalg.h"


void viewport(int x, int y, int w, int h, int d);

void lookat(Vec3f eye, Vec3f center, Vec3f up);

void projection(float coeff);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Vec3f *pts, float *z_buffer, float  *intensity, TGAImage &image);

TGAImage render_wireframe(const char *filename, TGAColor color, const int width, const int height);

TGAImage render_mesh(const char *filename, Vec3f light_direction, const int width, const int height);

Vec3f barycentric_coordinates(Vec3f a, Vec3f b, Vec3f c, Vec2i p);

Vec3f world2screen(Vec3f v, int width, int height);

#endif