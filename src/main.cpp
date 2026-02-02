
#include <sil/sil.hpp>
#include <cmath>

int main()
{
    sil::Image image{500, 500};

    int ca = image.width() / 2;
    int cb = image.height() / 2;

    int r = 100;
    int thickness = 5; // thickness in pixels
    int n = 6; //number of circles

    for (int i = 0; i < n; ++i)
    {
        float angle = i * (2 * M_PI / n);
        int a = static_cast<int>(ca + r * std::cos(angle));
        int b = static_cast<int>(cb + r * std::sin(angle));

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
    }

    

    image.save("output/rosace.png");
}