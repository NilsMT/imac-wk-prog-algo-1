Superbe repo où on fait joujou avec des images

> ℹ️ le code de chaque exo se trouve dans [EXOS.md](./EXOS.md)

# Explications de trucs

Le résultat de l'exercice custom [⭐⭐ Animation Cercle Hachuré](./EXOS.md#-animation-cercle-hachuré) est due à une erreur où
j'ai ajouté une valeur à la mauvaise variable.

[![result](./output/hatched_animated_circle/ezgif.gif)](./output/hatched_animated_circle/ezgif.gif)

Résultat, j'ai incrémenté les x des pixels de 10 au lieu de la position du cercle ce qui fait cet effet hachuré ce qui fait que le cercle ne colorie que tout les 10 x.

---

Pour l'exercice [⭐⭐⭐ Colorer la height map selon une image de dégradé](./EXOS.md#-colorer-la-height-map-selon-une-image-de-dégradé)
j'ai décidé de reprendre la coloration de la height_map mais de me baser sur une image
qui contient un dégradé horizontal de couleur : [![color_map](./images/color_map.png)](./images/color_map.png)

Qui permet de coloré les valeurs allant de 0 (couleur à gauche) à 1 (couleur à droite), ce qui donne :

[![result](./output/diamond_square_colored_with_map.png)](./output/diamond_square_colored_with_map.png)

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
