# ⭐ Ne garder que le vert

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

# ⭐ Échanger les canaux

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

# ⭐ Noir & Blanc

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

# ⭐ Négatif

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

# ⭐ Dégradé

```cpp
#include <sil/sil.hpp>

int main()
#include <sil/sil.hpp>

int main()
{
    sil::Image image{300 /*width*/, 200 /*height*/}; // Creates a black image with the given size.
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
