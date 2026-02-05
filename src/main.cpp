#include <sil/sil.hpp>
#include "random.hpp"
#include <array>
#include <cmath>
#include <iostream>

//config (you can change these)
const int n = 9;
const float hMin = 1.f;
const float hMax = 8.f;

//globals (don't touch)
float mapMin = 0.f;
float mapMax = 0.f;
const int mapSize = pow(2, n) + 1;
using arrayT = std::array<std::array<float, mapSize>, mapSize>;
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

sil::Image dithering(sil::Image image, float trs = 0.675f, int level = 2) {
    for (glm::vec3& color : image.pixels())
    {
        float c = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;

        color = glm::vec3{c};
    }

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

    return image;
}

/////////////////////////////////////

void fillArr(arrayT& arr, float value) {
    for (auto& row : arr) {
        for (auto& item : row) {
            item = value;
        }
    }
}

void updateMapMinMax(float value) {
    if (value < mapMin) {
        mapMin = value;
    }
    if (value > mapMax) {
        mapMax = value;
    }
}

void square_step(arrayT& arr, int size, int half, float r) {
    for (int iy = 0; iy < mapSize - 1; iy += size) {
        for (int ix = 0; ix < mapSize - 1; ix += size) {
            float x = arr[iy][ix]; //TL
            updateMapMinMax(x);
            float y = arr[iy][ix + size]; //TR
            updateMapMinMax(y);
            float z = arr[iy + size][ix]; //BL
            updateMapMinMax(z);
            float w = arr[iy + size][ix + size]; //BR
            updateMapMinMax(w);
            float c = (x + y + z + w) / 4; //C
            c += random_float(-r, r);
            updateMapMinMax(c);
            arr[iy + half][ix + half] = c;
        }
    }
}

void diamond_step(arrayT& arr, int size, int half, float r) {
    for (int iy = 0; iy < mapSize; iy += half) {
        for (int ix = (iy + half) % size; ix < mapSize; ix += size) {
            int count = 0;
            float sum = 0;

            //T
            if (iy - half >= 0) {
                sum += arr[iy - half][ix];
                count++;
            }
            //L
            if (ix - half >= 0) {
                sum += arr[iy][ix - half];
                count++;
            }
            //R
            if (ix + half < mapSize) {
                sum += arr[iy][ix + half];
                count++;
            }
            //B
            if (iy + half < mapSize) {
                sum += arr[iy + half][ix];
                count++;
            }

            float c = sum / count;
            c += random_float(-r, r);
            updateMapMinMax(c);
            arr[iy][ix] = c;
        }
    }
}

arrayT diamond_square_algorithm(float r) {
    arrayT height_map = {};
    fillArr(height_map, 0);

    //corners
    height_map[0][0] = random_float(hMin, hMax);
    height_map[0][mapSize - 1] = random_float(hMin, hMax);
    height_map[mapSize - 1][0] = random_float(hMin, hMax);
    height_map[mapSize - 1][mapSize - 1] = random_float(hMin, hMax);

    int chunk_size = mapSize - 1;

    while (chunk_size > 1) {
        int half = chunk_size / 2;
        square_step(height_map, chunk_size, half, r);
	    diamond_step(height_map, chunk_size, half, r);
        chunk_size /= 2;
        r /= 2;
    }
    return height_map;
}

sil::Image diamond_square() {
    sil::Image image{mapSize, mapSize};
    sil::Image color_map{"images/color_map.png"};
    float pre = 1.f / color_map.width();

    arrayT res = diamond_square_algorithm(8.0f);

    for (int y = 0; y < mapSize; ++y) {
        for (int x = 0; x < mapSize; ++x) {
            float& v = res[y][x];
            v = (v - mapMin) / (mapMax - mapMin);

            //coloring
            v = std::round(v / pre) * pre;//rounding
            glm::vec3 color;

            int color_x = static_cast<int>(v*color_map.width())-1;
            if (color_x < 0.f) {
                color_x = 0.f;
            } else if (color_x >= color_map.width()) {
                color_x = color_map.width() - 1;
            }
            color = color_map.pixel(color_x, 0);

            image.pixel(x, y) = color;
        }
    }
    return image;
}

int main() {
    //config
    float alpha = 0.5f; //how much the dithering should affect the final image (%)
    float trs = 0.675f; //threshold for dithering (high = brighter)
    int level = 2; //dithering level

    sil::Image image = diamond_square();
    sil::Image dithered = dithering(image, trs, level); //dithered act as luminosity map
    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {

            glm::vec3 color = image.pixel(x, y);
            float d = dithered.pixel(x, y).r;
            image.pixel(x, y) = glm::mix(color, color * d, alpha);
        }
    }
    image.save("output/diamond_color_dithering.png");
}

