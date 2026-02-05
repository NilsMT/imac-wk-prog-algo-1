#include <sil/sil.hpp>

int main() {
    sil::Image image{"images/banner.png"};

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y) {

        }

    }

    image.save("output/");
}