#include <sil/sil.hpp>
#include <cmath>
#include <vector>

using bayerT = std::vector<std::vector<float>>;

bayerT generateBayerLevel(int n) {
    if (n == 1) {
        //bayer at level 0
        return {
            { -0.5f,  0.5f },
            {  1.5f, -1.5f }
        };
    }

    bayerT prev = generateBayerLevel(n - 1);
    int size = prev.size();
    int newSize = size * 2;

    bayerT result(newSize, std::vector<float>(newSize));

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            float v = prev[y][x];

            //recursion
            result[y][x] = 4.0f * v + 0.0f;
            result[y][x + size] = 4.0f * v + 2.0f;
            result[y + size][x] = 4.0f * v + 3.0f;
            result[y + size][x + size] = 4.0f * v + 1.0f;
        }
    }

    return result;
}

int main() {
    //config
    float trs = 0.675f; //threshold shift [0;1] (the higher, the darker)
    int level = 2; //bayer level

    //1 : grayscale with sqrt(r^2 + g^2 + b^2)
    sil::Image image{"images/photo.jpg"};
    for (glm::vec3& color : image.pixels())
    {
        float c = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;

        color = glm::vec3{c};
    }

    image.save("output/dithering_before.png");

    //2 : dithering
    const auto bayer = generateBayerLevel(level);
    float maxB = pow(bayer.size(), 2);

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y) {
            
            const float brt = image.pixel(x,y).r;

            //bayer value
            float b = bayer[y % bayer.size()][x % bayer.size()];
            b = (b + 0.5f) / maxB; //normalize to [0,1]

            const float c = brt > trs - b
                ? 1.0 
                : 0.0;

            image.pixel(x,y) = glm::vec3{c};
        }
        
    }
    
    image.save("output/dithering.png");
}