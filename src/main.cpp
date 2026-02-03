
#include <sil/sil.hpp>
#include <cmath>
#include <iostream>

struct Lab {float L; float a; float b;};
struct RGB {float r; float g; float b;};

RGB oklab_to_linear_srgb(Lab c) 
{
    float l_ = c.L + 0.3963377774f * c.a + 0.2158037573f * c.b;
    float m_ = c.L - 0.1055613458f * c.a - 0.0638541728f * c.b;
    float s_ = c.L - 0.0894841775f * c.a - 1.2914855480f * c.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return RGB{
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

/*
0 ≤ S ≤ 0.04045
===> L = S/12.92
0.04045 < S ≤ 1
===> L = ((S+0.055)/1.055)^2.4
*/
RGB linear_to_srgb(const RGB& linear) {
    RGB srgb;
    float channels[3] = {linear.r, linear.g, linear.b};
    for (int i = 0; i < 3; ++i) {
        float L = channels[i];
        if (L <= 0.0031308f) {
            channels[i] = L * 12.92f;
        } else {
            channels[i] = 1.055f * powf(L, 1.0f / 2.4f) - 0.055f;
        }
    }
    srgb.r = channels[0];
    srgb.g = channels[1];
    srgb.b = channels[2];
    return srgb;
}

int main()
{
    sil::Image lab_srgb{300, 200};
    auto lab_lrgb = lab_srgb;

    const Lab red_lab = Lab{0.628, 0.225, 0.126};
    const Lab green_lab = Lab{0.866, -0.234, 0.179};

    for (int x{0}; x < lab_srgb.width(); ++x)
    {
        for (int y{0}; y < lab_srgb.height(); ++y)
        {
            float rx = static_cast<float>(x) / static_cast<float>(lab_srgb.width() - 1);
            Lab lab_c = 
            Lab{
                red_lab.L + rx * (green_lab.L - red_lab.L),
                red_lab.a + rx * (green_lab.a - red_lab.a),
                red_lab.b + rx * (green_lab.b - red_lab.b)
            };
            //1 : to linear
            RGB linear_c = oklab_to_linear_srgb(lab_c);

            lab_lrgb.pixel(x, y) = glm::vec3{
                linear_c.r,linear_c.g,linear_c.b
            };
            //2 : to sRGB
            RGB srgb_c = linear_to_srgb(linear_c);

            lab_srgb.pixel(x, y) = glm::vec3{
                srgb_c.r,srgb_c.g,srgb_c.b
            };
        }
    }
    lab_srgb.save("output/lab_srgb.png");
    lab_lrgb.save("output/lab_linear_rgb.png");
}