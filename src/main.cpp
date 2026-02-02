#include <sil/sil.hpp>
#include <cmath>

glm::vec3 linear_to_oklab(const glm::vec3& linear) 
{
    float l = 0.4122214708f * linear.r + 0.5363325363f * linear.g + 0.0514459929f * linear.b;
    float m = 0.2119034982f * linear.r + 0.6806995451f * linear.g + 0.1073969566f * linear.b;
    float s = 0.0883024619f * linear.r + 0.2817188376f * linear.g + 0.6299787005f * linear.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return glm::vec3{
        0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_,
        1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_,
        0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_
    };
}

/*
0 ≤ S ≤ 0.04045	
===> L = S/12.92
0.04045 < S ≤ 1
===> L = ((S+0.055)/1.055)^2.4
*/
glm::vec3 srgb_to_linear(const glm::vec3& srgb) {
    glm::vec3 linear;
    for (int i = 0; i < 3; ++i) {
        float c = srgb[i];
        if (c <= 0.04045f) {
            linear[i] = c * (1.0f / 12.92f);  // Linear section
        } else {
            linear[i] = powf((c + 0.055f) * (1.0f / 1.055f), 2.4f);  // Exponential section
        }
    }
    return linear;
}

int main()
{
    sil::Image image{300, 200};
    auto srgb = image;
    auto linear = image;
    auto oklab = image;

    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            float ry = static_cast<float>(y) / static_cast<float>(image.height() - 1);
            float rx = static_cast<float>(x) / static_cast<float>(image.width() - 1);
            glm::vec3 c = glm::vec3{1.0f - rx, rx, 0.0f};
            //1 : to linear
            glm::vec3 linear_c = srgb_to_linear(c);
            //2 : to oklab
            glm::vec3 lab_c = linear_to_oklab(linear_c);

            srgb.pixel(x, y) = c;
            linear.pixel(x, y) = linear_c;
            oklab.pixel(x, y) = lab_c;
        }
    }
    srgb.save("output/lab_srgb.png");
    linear.save("output/lab_linear.png");
    oklab.save("output/lab_oklab.png");
}