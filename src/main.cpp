
#include <sil/sil.hpp>

sil::Image blur(sil::Image image, int n) {
    float kernel[n][n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            kernel[i][j] = 1.0f / (n * n);

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

    return image;
}

sil::Image diff(sil::Image const& a, sil::Image const& b,float τ) {
    int w = a.width();
    int h = a.height();
    sil::Image res(w, h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            glm::vec3 d = a.pixel(x, y) - τ * b.pixel(x, y);
            res.pixel(x, y) = d;
        }
    }
    return res;
}

sil::Image grayscale(sil::Image image)
{
    for (glm::vec3& color : image.pixels())
    {
        float c = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;
        color = glm::vec3{c};
    }
    return image;
}

int main() {
    float T = 0.035f;  // threshold (lower = more edges)
    float τ = 0.95f; // scalar
    int σ = 5; // base blur radius
    int k = 2; // second blur scale factor

    sil::Image image("images/photo.jpg");

    //grayscale (because acerola cheated)
    image = grayscale(image);

    auto blurred_1 = blur(image, σ);
    auto blurred_2 = blur(image, k * σ);

    auto jungle_diff = diff(blurred_1, blurred_2, τ);

    for (int y = 0; y < jungle_diff.height(); ++y) {
        for (int x = 0; x < jungle_diff.width(); ++x) {
            jungle_diff.pixel(x, y) =
                jungle_diff.pixel(x, y).r > T ?
                    glm::vec3(0.0f) : glm::vec3(1.0f);
        }
    }
    
    jungle_diff.save("output/gaussians_diff.png");
}