#include <sil/sil.hpp>

int main()
{
    sil::Image image{300 /*width*/, 200 /*height*/}; // Creates a black image with the given size.
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
    image.save("output/gradient.png");
}