#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    auto base = image;

    //kernel
    float kernel[3][3] = {
        {0.0625,0.125,0.0625},
        {0.125,0.25,0.125},
        {0.0625,0.125,0.0625}
    };

    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            glm::vec3 new_color{0.0f};

            // apply the kernel
            for (int kx{-1}; kx <= 1; ++kx)
            {
                for (int ky{-1}; ky <= 1; ++ky)
                {
                    int sample_x = glm::clamp(x + kx, 0, image.width() - 1);
                    int sample_y = glm::clamp(y + ky, 0, image.height() - 1);
                    new_color += base.pixel(sample_x, sample_y) * kernel[kx + 1][ky + 1];
                }
            }

            image.pixel(x, y) = glm::clamp(new_color, 0.0f, 1.0f);
        }
    }
    image.save("output/convolution.png");
}