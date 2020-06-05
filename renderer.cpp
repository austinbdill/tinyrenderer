#include "renderer.h"
#include "tgaimage.h"
#include "linalg.h"
#include "mesh.h"

Matrix<float, 4, 4> Modelview = Matrix<float, 4, 4>::identity();
Matrix<float, 4, 4> Viewport = Matrix<float, 4, 4>::identity();
Matrix<float, 4, 4> Projection = Matrix<float, 4, 4>::identity();

void viewport(int x, int y, int w, int h, int d) {
    Viewport = Matrix<float, 4, 4>::identity();
    Viewport(0, 3) = x+w/2.f;
    Viewport(1, 3) = y+h/2.f;
    Viewport(2, 3) = d/2.f;

    Viewport(0, 0) = w/2.f;
    Viewport(1, 1) = h/2.f;
    Viewport(2, 2) = d/2.f;
}

void lookat(Vec3f eye, Vec3f center, Vec3f up) {
    Vec3f z = normalize(eye-center);
    Vec3f x = normalize(cross(up,z));
    Vec3f y = normalize(cross(z,x));
    Matrix<float, 4, 4> Minv = Matrix<float, 4, 4>::identity();
    Matrix<float, 4, 4> Tr   = Matrix<float, 4, 4>::identity();
    for (int i=0; i<3; i++) {
        Minv(0, i) = x[i];
        Minv(1, i) = y[i];
        Minv(2, i) = z[i];
        Tr(i, 3) = -center[i];
    }
    Modelview = Minv*Tr;
}

void projection(float coeff) {
    Projection = Matrix<float, 4, 4>::identity();
    Projection(3, 2) = coeff;
}

TGAImage render_mesh(const char *filename, Vec3f light_direction, const int width, const int height) {
    Mesh *model = NULL;

    model = new Mesh(filename);

    TGAImage image(width, height, TGAImage::RGB);
    float *z_buffer = new float[width*height];
    for (int i = 0; i < width*height; i++) {
        z_buffer[i] = std::numeric_limits<float>::min();
    }

    light_direction = normalize(project((Projection*Modelview*embed(light_direction, 0.f))));
    for (int i=0; i<model->nfaces(); i++) { 
        std::vector<int> face = model->face(i); 
        Vec3f screen_coords[3]; 
        Vec3f world_coords[3];
        float intensity[3];
        for (int j=0; j<3; j++) { 
            Vec3f v = model->vert(face[j]); 
            world_coords[j] = v;
            //screen_coords[j] = world2screen(v, width, height);
            screen_coords[j] = partial_round(project(Viewport*Projection*Modelview*embed(v, 1.f)));
            intensity[j] = dot(model->normal(i, j), light_direction);
        }
        triangle(screen_coords, z_buffer, intensity,  image); 
    }
    delete [] z_buffer;
    delete model;
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

Vec3f barycentric_coordinates(Vec3f a, Vec3f b, Vec3f c, Vec2i p) {

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

void triangle(Vec3f *pts, float *z_buffer, float *intensity, TGAImage &image) {
    int width = image.get_width();
    Vec2i bbmin(image.get_width()-1,  image.get_height()-1); 
    Vec2i bbmax(0, 0); 
    Vec2i clamp(image.get_width()-1, image.get_height()-1); 
    for (int i=0; i<3; i++) { 
        for (int j=0; j<2; j++) { 
            bbmin[j] = std::max(0,        std::min(bbmin[j], int(pts[i][j]))); 
            bbmax[j] = std::min(clamp[j], std::max(bbmax[j], int(pts[i][j]))); 
        } 
    }
    Vec2i p;
    float z;
    int z_position;
    for (p[0]=bbmin[0]; p[0]<=bbmax[0]; p[0]++) { 
        for (p[1]=bbmin[1]; p[1]<=bbmax[1]; p[1]++) { 
            Vec3f bc_screen  = barycentric_coordinates(pts[0], pts[1], pts[2], p);
            if (bc_screen[0] >=0 && bc_screen[1] >= 0 && bc_screen[2] >= 0) {
                z = bc_screen[0]*pts[0][2] + bc_screen[1]*pts[1][2] + bc_screen[2]*pts[2][2];
                z_position = int(p[0]+width*p[1]);
                float ity = intensity[0]*bc_screen[0] + intensity[1]*bc_screen[1] + intensity[2]*bc_screen[2];
                if (z > z_buffer[z_position]) {
                    image.set(p[0], p[1], TGAColor(255, 255, 255)*ity);
                    z_buffer[z_position] = z;
                } 
            }
        } 
    } 

}

Vec3f world2screen(Vec3f v, int width, int height) {
    return Vec3f(int(round((v[0]+1.)*width/2.+.5)), int(round((v[1]+1.)*height/2.+.5)), v[2]);
}