#include <sil/sil.hpp>
#include "random.hpp"

int main()
{
    set_random_seed(0);
    sil::Image image{"images/logo.png"};
    
    int n = 250; //number of glitch (the more the messier)
    int min_size_x = 10;
    int min_size_y = 5;
    int max_size_x = 20;
    int max_size_y = 10;

    for (int i = 0; i < n; ++i)
    {
        //rectangle
        glm::vec2 rectangle{
            random_int(min_size_x, max_size_x), 
            random_int(min_size_y, max_size_y)
        };
        //where is r1
        glm::vec2 pos_r1{
            random_int(0, image.width() - rectangle.x - 1),
            random_int(0, image.height() - rectangle.y - 1)
        };

        //where is r2
        glm::vec2 pos_r2{
            random_int(0, image.width() - rectangle.x - 1),
            random_int(0, image.height() - rectangle.y - 1)
        };

        //swap on image based on base
        for (int x{0}; x < (image.width()); ++x)
        {
            for (int y{0}; y < (image.height()); ++y)
            {
                //if in r1 --> swap with equivalent in r2
                if (x >= pos_r1.x && x < pos_r1.x + rectangle.x && y >= pos_r1.y && y < pos_r1.y + rectangle.y)
                {

                    int sample_x = glm::clamp(static_cast<int>(pos_r2.x) + x, 0, image.width() - 1);
                    int sample_y = glm::clamp(static_cast<int>(pos_r2.y) + y, 0, image.height() - 1);


                    std::swap(image.pixel(x,y),image.pixel(sample_x,sample_y));
                }
            }
        }
    }
    
    image.save("output/glitch.png");
}