#include <sil/sil.hpp>
#include <array>

int main()
{
    sil::Image image{"images/photo.jpg"};
    auto base = image;

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            std::array<glm::vec3, 4> regions{
                glm::vec3{0.f}, glm::vec3{0.f}, glm::vec3{0.f}, glm::vec3{0.f}
            };
            std::array<float, 4> counts{
                0.f, 0.f, 0.f, 0.f
            };

            //mean accumulation on 5x5 (-2 to 2 based on center)
            for (int kx = -2; kx <= 2; ++kx)
            {
                for (int ky = -2; ky <= 2; ++ky)
                {
                    int sx = glm::clamp(x + kx, 0, image.width() - 1);
                    int sy = glm::clamp(y + ky, 0, image.height() - 1);
                    glm::vec3 c = base.pixel(sx, sy);

                    int r =
                        (kx <= 0 && ky <= 0) ? 
                            0 : (kx >  0 && ky <= 0) ? 
                                1 : (kx <= 0 && ky >  0) ? 
                                    2 : 3;
                    
                    regions[r] += c; //+color
                    counts[r]  += 1.f; //+1 count
                }
            }

            std::array<glm::vec3, 4> means;
            for (int i = 0; i < 4; ++i)
                means[i] = regions[i] / counts[i];

            std::array<float, 4> dev{0.f, 0.f, 0.f, 0.f};

            //deviation (https://www.geeksforgeeks.org/maths/standard-deviation-formula/)
            for (int kx = -2; kx <= 2; ++kx)
            {
                for (int ky = -2; ky <= 2; ++ky)
                {
                    int r =
                        (kx <= 0 && ky <= 0) ? 0 :
                        (kx >  0 && ky <= 0) ? 1 :
                        (kx <= 0 && ky >  0) ? 2 : 3;

                    int sx = glm::clamp(x + kx, 0, image.width() - 1);
                    int sy = glm::clamp(y + ky, 0, image.height() - 1);
                    glm::vec3 c = base.pixel(sx, sy);

                    dev[r] += glm::distance(c, means[r]);
                }
            }

            //select smallest dev (= result)
            float minDev = sqrt(3.f);
            glm::vec3 res = image.pixel(x, y);

            for (int i = 0; i < 4; ++i)
            {
                dev[i] /= counts[i];

                if (dev[i] < minDev)
                {
                    minDev = dev[i];
                    res = means[i];
                }
            }

            image.pixel(x, y) = res;
        }
    }

    image.save("output/kuwahara.png");
}