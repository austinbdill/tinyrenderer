#include "tgaimage.h"
#include "linalg.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
        //TGAImage image(100, 100, TGAImage::RGB);
        //image.set(52, 41, red);
        //image.flip_vertically();
        //image.write_tga_file("output.tga");
        Vec3i m(0, 1, 2);
        Vec3i n(3, 4, 5);
        std::cout << m << std::endl;
        return 0;
}
