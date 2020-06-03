#include "tgaimage.h"
#include "renderer.h"
#include "linalg.h"
#include "mesh.h"

int main(int argc, char** argv) {

    const TGAColor white = TGAColor(255, 255, 255, 255);
    //const TGAColor red   = TGAColor(255, 0,   0,   255);
    TGAImage frame = render_mesh("obj/african_head/african_head.obj", Vec3f(0, 0, -1), white, 800, 800);
    frame.flip_vertically(); // to place the origin in the bottom left corner of the image 
    frame.write_tga_file("framebuffer.tga");
    return 0;
}
