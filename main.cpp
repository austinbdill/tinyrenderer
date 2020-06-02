#include "tgaimage.h"
#include "renderer.h"
#include "linalg.h"
#include "mesh.h"

int main(int argc, char** argv) {

    const TGAColor white = TGAColor(255, 255, 255, 255);
    const TGAColor red   = TGAColor(255, 0,   0,   255);
    TGAImage frame = render_mesh("obj/african_head/african_head.obj", red, 800, 800);
    frame.flip_vertically(); // to place the origin in the bottom left corner of the image 
    frame.write_tga_file("framebuffer.tga");
    return 0;


    /*const TGAColor white = TGAColor(255, 255, 255, 255);
    const TGAColor red   = TGAColor(255, 0,   0,   255);
    Mesh *model = NULL;
    const int width  = 800;
    const int height = 800;


    if (2==argc) {
        model = new Mesh(argv[1]);
    } else {
        model = new Mesh("obj/african_head/african_head.obj");
    }

    std::cout << model->nfaces() <<  std::endl;


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
            line(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
    */
}
