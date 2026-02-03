#include <sil/sil.hpp>
#include "random.hpp"
#include <array>
#include <cmath>

//config (you can change these)
const int n = 8;
const float hMin = 1.0f;
const float hMax = 8.0f;

//globals (don't touch)
float mapMin = 0;
float mapMax = 0;
const int mapSize = pow(2, n) + 1;
using arrayT = std::array<std::array<float, mapSize>, mapSize>;

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

/////////////////////////////////////

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

int main() {
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
            color = color_map.pixel(static_cast<int>(v*color_map.width())-1, 0);

            image.pixel(x, y) = color;
        }
    }
    image.save("output/diamond_square_colored_with_map.png");
}