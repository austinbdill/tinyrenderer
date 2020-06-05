#include "tgaimage.h"
#include "renderer.h"
#include "linalg.h"
#include "mesh.h"

int main(int argc, char** argv) {

    Vec3f light_dir(1,-1,1);
    Vec3f eye(1,1,3);
    Vec3f center(0,0,0);
    Vec3f up(0,0,1);

    const int height(800);
    const int width(800);
    const int depth(1);

    lookat(eye, center, up);
    viewport(width/8, height/8, width*3/4, height*3/4, depth);
    projection(-1.f/norm(eye-center));

    TGAImage frame = render_mesh("obj/african_head/african_head.obj", light_dir, height, width);
    frame.flip_vertically(); // to place the origin in the bottom left corner of the image 
    frame.write_tga_file("framebuffer.tga");
    //Vec3f a = Vec3f(0., 10., 2.);
    //Vec2f c = project(a);
    //std::cout << c << std::endl;
    return 0;
}
