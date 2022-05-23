# PROJET INFORMATIQUE GROUPE 10

Afin de lancer Oriieflamme: La Grande Guerre DDRS :
- taper la commande `make`
- executer le jeu grâce à la commande `./bin/jeu`

Quelques petites précision avant de vous lancer dans cette guerre de Développement Durable et de Responsabilité Sociétale :

Le système de coordonnées du plateau fonctionne ainsi :

```
+------->x (Abscisse)
|
|
|
|
v
y (Ordonnée)
```

> La faction (le joueur) qui débute est définie de façon aléatoire.

        




Amusez vous!!

# Important

## Installation bibliothèques nécessaires

Tout d'abord il faut installer SDL. Pour ce faire sur Linux/Unix il faut éxécuter ses lignes de code dans un terminal:

    ```
    git clone https://github.com/libsdl-org/SDL
    cd SDL
    mkdir build
    cd build
    ../configure
    make
    sudo make install   
    ```

Puis il faut installer sdl_image. Sur Linux/Unix il suffit de faire:

    ```
    sudo apt update
    sudo apt install libsdl2-image-dev
    ```