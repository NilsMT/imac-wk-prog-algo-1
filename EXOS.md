# Sommaire

- [Exos](#exos)
    - [⭐ Ne garder que le vert ✅](#-ne-garder-que-le-vert)
    - [⭐ Échanger les canaux ✅](#-échanger-les-canaux)
    - [⭐ Noir & Blanc ✅](#-noir--blanc)
    - [⭐ Négatif ✅](#-négatif)
    - [⭐ Dégradé ✅](#-dégradé)
    - [⭐⭐ Miroir ✅](#-miroir)
    - [⭐⭐ Image bruitée ✅](#-image-bruitée)
    - [⭐⭐ Rotation de 90° ✅](#-rotation-de-90)
    - [⭐⭐ RGB split ✅](#-rgb-split)
    - [⭐⭐ Luminosité ✅](#-luminosité)
    - [⭐⭐(⭐) Disque ✅](#-disque)
        - [⭐⭐⭐ Cercle ✅](#-cercle)
        - [⭐⭐ Animation ✅](#-animation)
        - [⭐⭐⭐ Rosace ✅](#-rosace)
    - [⭐⭐ Mosaïque ✅](#-mosaïque)
        - [⭐⭐⭐⭐ Mosaïque miroir](#-mosaïque-miroir)
    - [⭐⭐⭐ Glitch ✅](#-glitch)
    - [⭐⭐⭐ Tri de pixels](#-tri-de-pixels)
    - [⭐⭐⭐(⭐) Fractale de Mandelbrot](#-fractale-de-mandelbrot)
    - [⭐⭐⭐(⭐) Dégradés dans l'espace de couleur Lab](#-dégradés-dans-lespace-de-couleur-lab)
    - [⭐⭐⭐(⭐) Tramage](#-tramage)
    - [⭐⭐⭐(⭐) Normalisation de l'histogramme ✅](#-normalisation-de-lhistogramme)
    - [⭐⭐⭐⭐ Vortex](#-vortex)
    - [⭐⭐⭐⭐ Convolutions ✅](#-convolutions)
        - [⭐ Netteté, Contours, etc. ✅](#-netteté-contours-etc)
        - [⭐⭐ Filtres séparables](#-filtres-séparables)
        - [⭐⭐ Différence de gaussiennes](#-différence-de-gaussiennes)
    - [⭐⭐⭐⭐⭐ K-means : trouver les couleurs les plus présentes dans une image](#-k-means--trouver-les-couleurs-les-plus-présentes-dans-une-image)
    - [⭐⭐⭐⭐⭐ Filtre de Kuwahara (effet peinture à l'huile)](#-filtre-de-kuwahara-effet-peinture-à-lhuile)
    - [⭐⭐⭐⭐⭐⭐ Diamond Square](#-diamond-square)
        - [⭐⭐ Colorer la height map](#-colorer-la-height-map)
- [Custom](#custom)
    - [⭐⭐ Animation Cercle Hachuré ✅](#-animation-cercle-hachuré)

# Exos

## ⭐ Ne garder que le vert

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/logo.png"};
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
    sil::Image image{300, 200};
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
    image.save("output/gradient.png");
}
```

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

### ⭐⭐⭐ Cercle

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

### ⭐⭐ Animation

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

### ⭐⭐⭐ Rosace

```cpp
#include <sil/sil.hpp>
#include <cmath>

int main()
{
    sil::Image image{500, 500};

    int ca = image.width() / 2;
    int cb = image.height() / 2;

    int r = 100;
    int thickness = 5; // thickness in pixels
    int n = 6; //number of circles

    for (int i = 0; i < n; ++i)
    {
        float angle = i * (2 * M_PI / n);
        int a = static_cast<int>(ca + r * std::cos(angle));
        int b = static_cast<int>(cb + r * std::sin(angle));

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
    }



    image.save("output/rosace.png");
}
```

## ⭐⭐ Mosaïque

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image base{"images/logo.png"};

    int n = 5;

    sil::Image image{base.width() * n, base.height() * n};

    for (int x{0}; x < (image.width()); ++x)
    {
        for (int y{0}; y < (image.height()); ++y)
        {
            image.pixel(x,y) = base.pixel(x % base.width(),y % base.height());
        }
    }
    image.save("output/mosaic.png");
}
```

### ⭐⭐⭐⭐ Mosaïque miroir

```cpp
//TODO: > ⭐⭐⭐⭐ Mosaïque miroir
```

## ⭐⭐⭐ Glitch

```cpp
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
```

## ⭐⭐⭐ Tri de pixels

```cpp
//TODO: ⭐⭐⭐ Tri de pixels
```

## ⭐⭐⭐(⭐) Fractale de Mandelbrot

```cpp
//TODO: ⭐⭐⭐(⭐) Fractale de Mandelbrot
```

## ⭐⭐⭐(⭐) Dégradés dans l'espace de couleur Lab

```cpp
//TODO: ⭐⭐⭐(⭐) Dégradés dans l'espace de couleur Lab
```

## ⭐⭐⭐(⭐) Tramage

```cpp
//TODO: ⭐⭐⭐(⭐) Tramage
```

## ⭐⭐⭐(⭐) Normalisation de l'histogramme

```cpp
#include <sil/sil.hpp>
/* https://aampe.com/blog/how-to-normalize-data-in-excel */

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
```

## ⭐⭐⭐⭐ Vortex

```cpp
//TODO: ⭐⭐⭐⭐ Vortex
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
        {0.0625,0.125,0.0625},
        {0.125,0.25,0.125},
        {0.0625,0.125,0.0625}
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

### ⭐ Netteté, Contours, etc.

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
    image.save("output/contours.png");
}
```

## ⭐⭐ Filtres séparables

```cpp
//TODO: > ⭐⭐ Filtres séparables
```

## ⭐⭐ Différence de gaussiennes

```cpp
//TODO: > ⭐⭐ Différence de gaussiennes
```

## ⭐⭐⭐⭐⭐ K-means : trouver les couleurs les plus présentes dans une image

```cpp
//TODO: ⭐⭐⭐⭐⭐ K-means : trouver les couleurs les plus présentes dans une image
```

## ⭐⭐⭐⭐⭐ Filtre de Kuwahara (effet peinture à l'huile)

```cpp
//TODO: ⭐⭐⭐⭐⭐ Filtre de Kuwahara (effet peinture à l'huile)
```

## ⭐⭐⭐⭐⭐⭐ Diamond Square

```cpp
//TODO: ⭐⭐⭐⭐⭐⭐ Diamond Square
```

### ⭐⭐ Colorer la height map

```cpp
//TODO: > ⭐⭐ Colorer la height map
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
