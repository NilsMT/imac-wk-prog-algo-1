#include <sil/sil.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include "random.hpp"

//based on https://www.geeksforgeeks.org/machine-learning/k-means-clustering-introduction/
int main()
{
    sil::Image image{"images/photo.jpg"};
    auto base = image;
    //config
    const int k = 16; //number of centroids (colors)
    const int max_iters = 10; //how much tries to update centroids (high = more accurate)

    const int w = image.width();
    const int h = image.height();

    //pick initialize k random centroids
    std::vector<glm::vec3> centroids(k);
    for (int i = 0; i < k; ++i)
    {
        int x = random_int(0, w - 1);
        int y = random_int(0, h - 1);
        centroids[i] = base.pixel(x, y);
    }

    //iterate k-means until max_iters
    for (int iter = 0; iter < max_iters; ++iter)
    {
        std::vector<glm::vec3> sums(k, glm::vec3{0.f});
        std::vector<int> counts(k, 0);

        //pixels assigned to closest centroid
        for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
        {
            glm::vec3 c = base.pixel(x, y);
            float minDist = sqrt(3.f);  //max distance is (1,1,1) to (0,0,0)
            int best = 0;
            for (int i = 0; i < k; ++i)
            {
                float d = glm::distance(c, centroids[i]);
                if (d < minDist)
                {
                    minDist = d;
                    best = i;
                }
            }
            sums[best] += c;
            counts[best] += 1;
        }

        //update centroids
        for (int i = 0; i < k; ++i)
            if (counts[i] > 0)
                centroids[i] = sums[i] / float(counts[i]);
    }

    //recolor image using nearest centroid
    for (int y = 0; y < h; ++y)
    for (int x = 0; x < w; ++x)
    {
        glm::vec3 c = base.pixel(x, y);
        float minDist = std::numeric_limits<float>::max();
        int best = 0;
        for (int i = 0; i < k; ++i)
        {
            float d = glm::distance(c, centroids[i]);
            if (d < minDist)
            {
                minDist = d;
                best = i;
            }
        }
        image.pixel(x, y) = centroids[best];
    }

    image.save("output/kmeans.png");
}