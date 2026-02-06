![](./images/banner.png)

# Description

Superbe repo où on fait joujou avec des images

# Arborescence

> ℹ️ le code de chaque exo et leurs images associées se trouve dans [EXOS.md](./EXOS.md).
>
> Je conseille également d'utilisé l'`outline` sur le panneau de gauche de VS Code pour naviguer

```
📁 build            : fichiers de build (gitignored)
📁 images           : images d'input
📁 lib
   └── 📁 sil       : librairie pour modifier les images
📁 output           : images d'output
📁 src
   └──  📄 main.cpp : le fichier principale
📄 README.md        : le rapport
📄 EXOS.md          : le code de chaque exercice
```

# Rapport

L'exercice [⭐ Différence](./EXOS.md#-différence) est un code qui permet d'avoir la différence entre deux images

---

Le résultat de l'exercice custom [⭐⭐ Animation Cercle Hachuré](./EXOS.md#-animation-cercle-hachuré) est due à une erreur où
j'ai ajouté une valeur à la mauvaise variable.

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

        [...];
        //                                    👇 ICI
        for (int x{0}; x < image.width(); x += tr)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                [...];
            }
        }

        [...];
    }
}
```

Résultat, j'ai incrémenté les `x` des pixels de 10 au lieu de la position (`a`) du cercle ce qui fait cet effet hachuré ce qui fait que le cercle ne colorie que tout les 10 `x`.

[![](./output/hatched_animated_circle/ezgif.gif)](./output/hatched_animated_circle/ezgif.gif)

---

Pour l'exercice [⭐⭐⭐ Colorer la height map selon une image de dégradé](./EXOS.md#-colorer-la-height-map-selon-une-image-de-dégradé)
j'ai décidé de reprendre la coloration de la height_map mais de me baser sur une image
qui contient un dégradé horizontal de couleur : [![color_map](./images/color_map.png)](./images/color_map.png)

Qui permet de colorer les valeurs allant de 0 (couleur à gauche) à 1 (couleur à droite), ce qui donne :

[![](./output/diamond_color_map.png)](./output/diamond_color_map.png)

---

Voici une comparaison du temps d'exécution entre l'exercice
[⭐⭐ Filtres séparables](./EXOS.md#-filtres-séparables) (optimisé) et
[⭐⭐⭐⭐ Convolutions](./EXOS.md#-convolutions) (naïf) :

| Taille du kernel | Temps Naïf (s) | Temps Optimisé (s) | Efficacité |
| ---------------- | -------------- | ------------------ | ---------- |
| 8                | 0.139486       | 0.032982           | x4         |
| 16               | 0.507313       | 0.06249            | x8         |
| 32               | 1.90005        | 0.109926           | x19        |
| 64               | 7.51449        | 0.204911           | x38        |
| 128              | 30.6175        | 0.41851            | x75        |
| 256              | 125.253        | 0.830643           | x151       |

---

Pour [⭐ Différence](./EXOS.md#-différence) j'ai juste fait une fonction qui soustrait les canaux `R,G,B`, cette fonction a été utilisée dans [⭐⭐ Différence de gaussiennes](./EXOS.md#-différence-de-gaussiennes).

---

L'exercice [⭐⭐⭐ Height map stylisée](./EXOS.md#-height-map-stylisée) reprend
[⭐⭐⭐ Colorer la height map selon une image de dégradé](./EXOS.md#-colorer-la-height-map-selon-une-image-de-dégradé)
et utilise [⭐⭐⭐(⭐) Tramage](./EXOS.md#-tramage) en tant que map sur la luminosité,
ce qui donne un effet texturé sur le terrain

[![](./output/diamond_color_dithering.png)](./output/diamond_color_dithering.png)
