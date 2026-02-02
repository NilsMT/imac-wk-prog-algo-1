#include <sil/sil.hpp>
#include <algorithm>

int main()
{
    sil::Image image{"images/logo.png"};
    
    //lambda exp that turn color into grayscale
    auto grayscale = [](const glm::vec3 &c){
        return glm::dot(c, glm::vec3{0.3f, 0.59f, 0.11f});
    };

    //sort each column by luminance
    for (int x{0}; x < image.width(); ++x)
    {
        //get column
        std::vector<glm::vec3> column;

        //append pixels to column
        for (int y{0}; y < image.height(); ++y)
            column.push_back(image.pixel(x, y));

        //sort column by luminance (worse up, better down)
        std::sort(column.begin(), column.end(), [&](const glm::vec3 &a, const glm::vec3 &b){
            return grayscale(a) > grayscale(b);
        });

        //write back in the image
        for (int y{0}; y < image.height(); ++y)
            image.pixel(x, y) = column[y];
    }

    image.save("output/sorted.png");
}