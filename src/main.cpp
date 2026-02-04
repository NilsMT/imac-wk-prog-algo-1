#include <sil/sil.hpp>
#include <chrono>
#include <iostream>


double main_naif(int n) {
    auto start = std::chrono::high_resolution_clock::now();

    /////////////////////////////////////////////////////
    sil::Image image{"images/logo.png"};
    auto base = image;

    //kernel
    float kernel[n][n];

    // Fill a 16x16 box blur kernel
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            kernel[i][j] = 1.0f / (n * n);

    int w = image.width();
    int h = image.height();
    int halfn = n / 2;

    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            glm::vec3 new_color(0.0f);

            // apply the kernel (naive 2D convolution)
            for (int kx = 0; kx < n; ++kx) {
                for (int ky = 0; ky < n; ++ky) {
                    int sample_x = glm::clamp(x + kx - halfn, 0, w - 1);
                    int sample_y = glm::clamp(y + ky - halfn, 0, h - 1);
                    new_color += base.pixel(sample_x, sample_y) * kernel[kx][ky];
                }
            }

            image.pixel(x, y) = glm::clamp(new_color, 0.0f, 1.0f);
        }
    }

    ///////////////////////
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    std::chrono::duration<double> elapsed = end - start;

    return elapsed.count();
}

double main_opti(int n) {
    auto start = std::chrono::high_resolution_clock::now();

    /////////////////////////////////////////////////////
    //define the kernel here
    float kernel[n][n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            kernel[i][j] = 1.0f / (n * n);

    sil::Image image{"images/logo.png"};
    auto base = image; //result
    auto temp = image; //temp for x pass

    int w = image.width();
    int h = image.height();
    float kernelX[n];
    float kernelY[n];

    //separate kernel
    for (int j = 0; j < n; ++j) kernelX[j] = kernel[0][j];
    for (int i = 0; i < n; ++i) kernelY[i] = kernel[i][0] / kernelX[0];

    int halfn = n / 2;

    //x pass
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            glm::vec3 sum(0.0f);
            for (int k = 0; k < n; ++k) {
                int sx = glm::clamp(x + k - halfn, 0, w - 1);
                sum += base.pixel(sx, y) * kernelX[k];
            }
            temp.pixel(x, y) = sum;
        }
    }

    //y pass
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            glm::vec3 sum(0.0f);
            for (int k = 0; k < n; ++k) {
                int sy = glm::clamp(y + k - halfn, 0, h - 1);
                sum += temp.pixel(x, sy) * kernelY[k];
            }
            image.pixel(x, y) = glm::clamp(sum, 0.0f, 1.0f);
        }
    }

    ///////////////////////
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    std::chrono::duration<double> elapsed = end - start;
    
    return elapsed.count();
}


int main() {
    int sizes[] = {8, 16, 32, 64, 128, 256};

    for (int n : sizes) {
        double tn = main_naif(n);
        double to = main_opti(n);
        std::cout << "| " << n << " | " << tn << "s | " << to << "s |\n";
    }

    return 0;
}