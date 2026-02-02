# ⭐ Exos

## ⭐ Ne garder que le vert

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    // TODO: modifier l'image
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
    image.save("output/keep_green_only.png");
}
```

## ⭐ Échanger les canaux

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    // TODO: modifier l'image
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.g, color.r);
        std::swap(color.b, color.g);
    }
    image.save("output/swap.png");
}
```

## ⭐ Noir & Blanc

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    // TODO: modifier l'image
    for (glm::vec3& color : image.pixels())
    {
        float c = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;

        color.r = c;
        color.g = c;
        color.b = c;
    }
    image.save("output/grayscale.png");
}
```

## ⭐ Négatif

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    // TODO: modifier l'image
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
    image.save("output/negate.png");
}
```

## ⭐ Dégradé

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    // TODO: modifier l'image
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
    image.save("output/negate.png");
}
```

## ⭐ Netteté, Contours, etc.

```cpp
//TODO: XXX
```

# ⭐⭐ Exos

## ⭐⭐ Miroir

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    for (int x{0}; x < image.width() / 2; ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            int mirrorX = image.width() - 1 - x;

            std::swap(image.pixel(x,y), image.pixel(mirrorX,y));
        }
    }
    image.save("output/mirror.png");
}
```

## ⭐⭐ Image bruitée

```cpp
#include <sil/sil.hpp>
#include "random.hpp"

int main()
{
    set_random_seed(0);

    sil::Image image{"images/logo.png"};
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = random_float(0.0f, 1.0f) < 0.5f ?
                glm::vec3(random_float(0.0f, 1.0f), random_float(0.0f, 1.0f), random_float(0.0f, 1.0f)) : image.pixel(x, y);
        }
    }
    image.save("output/noise.png");
}
```

## ⭐⭐ Rotation de 90°

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    sil::Image rotated_image{image.height(), image.width()};
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            rotated_image.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }
    rotated_image.save("output/rotated.png");
}
```

## ⭐⭐ RGB split

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    sil::Image split_image{image.width(), image.height()};

    int offset = 20;

    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {

            split_image.pixel(x, y) = image.pixel(x, y);


            split_image.pixel(x, y).r = x-offset >= 0 ?
                image.pixel(x - offset, y).r : 0.0f;

            split_image.pixel(x, y).g = x+offset < image.width() ?
                image.pixel(x + offset, y).g : 0.0f;
        }
    }
    split_image.save("output/split.png");
}
```

## ⭐⭐ Luminosité

```cpp
#include <sil/sil.hpp>
#include <cmath>

int main()
{
    sil::Image image{"images/photo.jpg"};
    double a = 0.8; // choose 0..5 (0.5 brightens, 2 darkens)
    for (glm::vec3& color : image.pixels()) {
        color.r = std::pow(color.r, a);
        color.g = std::pow(color.g, a);
        color.b = std::pow(color.b, a);
        color = glm::clamp(color, glm::vec3{0.0f}, glm::vec3{1.0f});
    }
}
```

## ⭐⭐ Filtres séparables

```cpp
//TODO: XXX
```

## ⭐⭐ Différence de gaussiennes

```cpp
//TODO: XXX
```

## ⭐⭐ Colorer la height map

```cpp
//TODO: XXX
```

## ⭐⭐ Mosaïque

```cpp
//TODO: XXX
```

## ⭐⭐ Animation

```cpp
#include <sil/sil.hpp>
#include <cmath>
#include <string>

int main()
{
    int r = 100;
    int spf = 10; // speed per frame

    for (int a = 0; a < 500; a+=spf) {

        sil::Image image{500, 500};
        int b = image.height() / 2;

        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                int dx = x - a;
                int dy = y - b;
                if (dx*dx + dy*dy <= r * r) {
                    image.pixel(x,y) = glm::vec3 {1.0f,1.0f,1.0f};
                }
            }
        }

        auto fileName = "output/animated_circle/" + std::to_string(a/spf) + ".png";
        image.save(fileName);
    }
}
```

## ⭐⭐(⭐) Disque

```cpp
#include <sil/sil.hpp>
/* https://fr.wikipedia.org/wiki/Disque_(g%C3%A9om%C3%A9trie) */

int main()
{
    sil::Image image{500/*width*/, 500/*height*/};

    int a = image.width() / 2;
    int b = image.height() / 2;

    int r = 100;

    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            int dx = x - a;
            int dy = y - b;
            if (dx*dx + dy*dy <= r * r) {
                image.pixel(x,y) = glm::vec3 {1.0f,1.0f,1.0f};
            }
        }
    }
    image.save("output/disc.png");
}
```

# ⭐⭐⭐ Exos

## ⭐⭐⭐ Cercle

```cpp
#include <sil/sil.hpp>
#include <cmath>

int main()
{
    sil::Image image{500, 500};

    int a = image.width() / 2;
    int b = image.height() / 2;

    int r = 100;
    int thickness = 5; // thickness in pixels

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            int dx = x - a;
            int dy = y - b;

            float dist = std::sqrt(dx * dx + dy * dy);

            if (std::abs(dist - r) <= thickness)
            {
                image.pixel(x, y) = glm::vec3{1.f, 1.f, 1.f};
            }
        }
    }

    image.save("output/circle.png");
}
```

## ⭐⭐⭐ Rosace

```cpp
//TODO: XXX
```

## ⭐⭐⭐ Glitch

```cpp
//TODO: XXX
```

## ⭐⭐⭐ Tri de pixels

```cpp
//TODO: XXX
```

## ⭐⭐⭐(⭐) Fractale de Mandelbrot

```cpp
//TODO: XXX
```

## ⭐⭐⭐(⭐) Dégradés dans l'espace de couleur Lab

```cpp
//TODO: XXX
```

## ⭐⭐⭐(⭐) Tramage

```cpp
//TODO: XXX
```

## ⭐⭐⭐(⭐) Normalisation de l'histogramme

```cpp
//TODO: XXX
```

# ⭐⭐⭐⭐ Exos

## ⭐⭐⭐⭐ Mosaïque miroir

```cpp
//TODO: XXX
```

## ⭐⭐⭐⭐ Vortex

```cpp
//TODO: XXX
```

## ⭐⭐⭐⭐ Convolutions

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
    auto base = image;

    //kernel
    float kernel[3][3] = {
        {-1,-1,-1},
        {-1,8,-1},
        {-1,-1,-1}
    };

    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            glm::vec3 new_color{0.0f};

            // apply the kernel
            for (int kx{-1}; kx <= 1; ++kx)
            {
                for (int ky{-1}; ky <= 1; ++ky)
                {
                    int sample_x = glm::clamp(x + kx, 0, image.width() - 1);
                    int sample_y = glm::clamp(y + ky, 0, image.height() - 1);
                    new_color += base.pixel(sample_x, sample_y) * kernel[kx + 1][ky + 1];
                }
            }

            image.pixel(x, y) = glm::clamp(new_color, 0.0f, 1.0f);
        }
    }
    image.save("output/convolution.png");
}
```

# ⭐⭐⭐⭐⭐ Exos

## ⭐⭐⭐⭐⭐ K-means : trouver les couleurs les plus présentes dans une image

```cpp
//TODO: XXX
```

## ⭐⭐⭐⭐⭐ Filtre de Kuwahara (effet peinture à l'huile)

```cpp
//TODO: XXX
```

# ⭐⭐⭐⭐⭐⭐ Exos

## ⭐⭐⭐⭐⭐⭐ Diamond Square

```cpp
//TODO: XXX
```

# Custom

## ⭐⭐ Animation Cercle Hachuré

```cpp
#include <sil/sil.hpp>
#include <cmath>
#include <string>

int main()
{
    int r = 100;
    int tr = 10; // threshold
    int spf = 10; // speed per frame

    for (int a = 0; a < 500; a+=spf) {

        sil::Image image{500, 500};
        int b = image.height() / 2;

        for (int x{0}; x < image.width(); x += tr)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                int dx = x - a;
                int dy = y - b;
                if (dx*dx + dy*dy <= r * r) {
                    image.pixel(x,y) = glm::vec3 {1.0f,1.0f,1.0f};
                }
            }
        }

        auto fileName = "output/hatched_animated_circle/" + std::to_string(a/spf) + ".png";
        image.save(fileName);
    }
}
```
