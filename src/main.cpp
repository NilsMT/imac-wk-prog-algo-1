#include <sil/sil.hpp>

int main()
{
    sil::Image base{"images/logo.png"};
    
    int n = 5;

    sil::Image image{base.width() * n, base.height() * n};

    for (int x{0}; x < (image.width()); ++x)
    {
        for (int y{0}; y < (image.height()); ++y)
        {
            image.pixel(x,y) = base.pixel(x % base.width(),y % base.height());
        }
    }
    image.save("output/mosaic.png");
}