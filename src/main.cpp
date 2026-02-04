#include <sil/sil.hpp>
#include <complex>
#include <cmath>
#include <iostream>

int main() {
    int size = 500;

    sil::Image image{size, size};

    float maxIter = 40.f;
    float range = 4.f;
    float shift = 2.f;

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {

            float cx = ((float)x / size) * range - shift; //[0;1] -> [0;4] -> [-2;2]
            float cy = ((float)y / size) * range - shift; //[0;1] -> [0;4] -> [-2;2]

            std::complex<float> c{
                cx,
                cy
            }; //c

            std::complex<float> z{0.f, 0.f}; //z = 0

            float iter = 0.f;
            while (std::abs(z) <= 2 && iter < maxIter) {
                z = z * z + c;
                ++iter;
            }

            image.pixel(x,y) = glm::vec3{iter/maxIter}; //col
        }
    }

    image.save("output/fractal.png");
}