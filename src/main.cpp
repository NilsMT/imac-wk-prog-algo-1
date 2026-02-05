#include <sil/sil.hpp>

int main() {
    //config (for a kernel that blur, otherwise define the kernel directly and change n value)
    const int n = 16; //kernel size

    //define the kernel here
    float kernel[16][16];
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

    temp.save("output/separable_filters_x.png");

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

    image.save("output/separable_filters_xy.png");
}