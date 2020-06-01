#include "renderer.h"
#include "tgaimage.h"

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