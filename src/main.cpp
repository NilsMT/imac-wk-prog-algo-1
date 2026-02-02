
#include <sil/sil.hpp>
#include <cmath>

int main()
{
    sil::Image image{500, 500};

    int a = image.width() / 2;
    int b = image.height() / 2;

    int r = 100;
    int thickness = 5; // thickness in pixels

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            int dx = x - a;
            int dy = y - b;

            float dist = std::sqrt(dx * dx + dy * dy);

            if (std::abs(dist - r) <= thickness)
            {
                image.pixel(x, y) = glm::vec3{1.f, 1.f, 1.f};
            }
        }
    }

    image.save("output/rosace.png");
}