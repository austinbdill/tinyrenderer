#include "renderer.h"
#include "tgaimage.h"
#include "linalg.h"

Vec3f barycentric_coordinates(Vec2i a, Vec2i b, Vec2i c, Vec2i p) {
    //std::cout << "a: " << a << std::endl;
    //std::cout << "b: " << b << std::endl;
    //std::cout << "c: " << c << std::endl;
    //std::cout << "p: " << p << std::endl;

    Vec2i ab(b[0]-a[0], b[1]-a[1]);
    //std::cout << "AB: " << ab << std::endl;
    Vec2i ac(c[0]-a[0], c[1]-a[1]);
    //std::cout << "AC: " << ac << std::endl;
    Vec2i pa(a[0]-p[0], a[1]-p[1]);
    //std::cout << "PA: " << pa << std::endl;
    Vec3i vec1(ac[0], ab[0], pa[0]);
    //std::cout << "vec1: " << vec1 << std::endl;
    Vec3i vec2(ac[1], ab[1], pa[1]);
    //std::cout << "vec2: " << vec2 << std::endl;
    Vec3f cross_product = cross(vec1, vec2);
    //std::cout << "cross: " << cross_product << std::endl;
    Vec3f result(1.f-(cross_product[0]+cross_product[1])/cross_product[2], cross_product[1]/cross_product[2], cross_product[0]/cross_product[2]);
    std::cout << "result: " << result << std::endl;
    return result;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false;
    // Determine major axis and assign it to the x-coordinate
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    // Ensure line is defined from left and right
    if (x0>x1) {  
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1 - x0;
    int dy = y1 - y0;
    int y = y0;
    int error = 0;
    int derror = std::abs(dy); 
    for (int x = x0; x <= x1; ++x) { 
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color); 
        }
        error += derror;
        if (error >= 0.5 * dx) {
            y += (y1>y0?1:-1);
            error -= dx;
        }
    } 
}

void triangle(Vec2i *pts, TGAImage &image, TGAColor color) {
    Vec2i bbmin(image.get_width()-1,  image.get_height()-1); 
    Vec2i bbmax(0, 0); 
    Vec2i clamp(image.get_width()-1, image.get_height()-1); 
    for (int i=0; i<3; i++) { 
        for (int j=0; j<2; j++) { 
            bbmin[j] = std::max(0,        std::min(bbmin[j], pts[i][j])); 
            bbmax[j] = std::min(clamp[j], std::max(bbmax[j], pts[i][j])); 
        } 
    }
    Vec2i p;
    for (p[0]=bbmin[0]; p[0]<=bbmax[0]; p[0]++) { 
        for (p[1]=bbmin[1]; p[1]<=bbmax[1]; p[1]++) { 
            Vec3f bc_screen  = barycentric_coordinates(pts[0], pts[1], pts[2], p);
            if (bc_screen[0] >=0 && bc_screen[1] >= 0 && bc_screen[2] >= 0) {
                image.set(p[0], p[1], color); 
            }
        } 
    } 

}
