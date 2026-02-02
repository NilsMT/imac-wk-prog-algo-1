#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/photo_faible_contraste.jpg"};

    glm::vec3 brightest{0.f};
    glm::vec3 darkest{1.f};

    //first : find brightest and darkest colors
    for (glm::vec3& color : image.pixels())
    {
        if (glm::any(glm::greaterThanEqual(color, brightest)))
            brightest = glm::max(brightest, color);
        if (glm::any(glm::lessThanEqual(color, darkest)))
            darkest = glm::min(darkest, color);
    }

    //second : histogram normalization
    for (glm::vec3& color : image.pixels())
    {
        auto c = (color - darkest)/(brightest-darkest);
        color = c;
    }
    image.save("output/histogram.png");
}