#include "renderer.h"
#include "tgaimage.h"
#include "linalg.h"
#include "mesh.h"

TGAImage render_mesh(const char *filename, TGAColor color, const int width, const int height) {
    Mesh *model = NULL;

    model = new Mesh(filename);

    TGAImage image(width, height, TGAImage::RGB);
    for (int i=0; i<model->nfaces(); i++) { 
        std::vector<int> face = model->face(i); 
        Vec2i screen_coords[3]; 
        for (int j=0; j<3; j++) { 
            Vec3f world_coords = model->vert(face[j]); 
            screen_coords[j] = Vec2i((world_coords[0]+1.)*width/2., (world_coords[1]+1.)*height/2.); 
        } 
        triangle(screen_coords, image, TGAColor(rand()%255, rand()%255, rand()%255, 255)); 
}
    return image;
}

TGAImage render_wireframe(const char *filename, TGAColor color, const int width, const int height) {
    Mesh *model = NULL;

    model = new Mesh(filename);

    TGAImage image(width, height, TGAImage::RGB);
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0[0]+1.)*width/2.;
            int y0 = (v0[1]+1.)*height/2.;
            int x1 = (v1[0]+1.)*width/2.;
            int y1 = (v1[1]+1.)*height/2.;
            line(x0, y0, x1, y1, image, color);
        }
    }
    return image;
}

Vec3f barycentric_coordinates(Vec2i a, Vec2i b, Vec2i c, Vec2i p) {

    Vec2i ab(b[0]-a[0], b[1]-a[1]);
    Vec2i ac(c[0]-a[0], c[1]-a[1]);
    Vec2i pa(a[0]-p[0], a[1]-p[1]);
    Vec3i vec1(ac[0], ab[0], pa[0]);
    Vec3i vec2(ac[1], ab[1], pa[1]);
    Vec3f cross_product = cross(vec1, vec2);
    Vec3f result(1.f-(cross_product[0]+cross_product[1])/cross_product[2], cross_product[1]/cross_product[2], cross_product[0]/cross_product[2]);
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
