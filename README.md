# Projet_systeme_fork
Projet effectué en langage de programmation c


il s'agit d'un projet effectué en licence 2 d'informatique. Celui ci consiste a utiliser les fork afin de faire des modification d'image 

Pour le programme de base : 

Le programme de base permet de modifier l'image en noir et blanc

-> pour lancer(compilation et exécution) le projet avec l'image donnée en exemple  : 

gcc -Wall copie_fichier.c -o main 

./main Classic.bmp 

Pour l'objectif premier :

ici on ajoute au programme de base l'ajout d'une copie du fichier sur lequel on soughaite travaillé


-> pour lancer(compilation et exécution) le projet avec l'image donnée en exemple : 

gcc -Wall copie_obj1.c -o main 
gcc -Wall fils.c -o fils

./main Classic.bmp copiefichier //avec copiefichier le nom du fichier que l'on souhaite donner à la copie qu'on va créer

Pour l'objectif second :

ici on ajoute 4 fils pour pouvoir faire 4 images et une copie a partir d'une image bmp 

-> pour lancer(compilation et exécution) le projet avec l'image donnée en exemple : 

gcc -Wall copie_obj2.c -o main 
gcc -Wall fils_gris.c -o g
gcc -Wall fils_rouge -o r
gcc -Wall fils_bleu -o b
gcc -Wall fils_vert -o v

./main Classic.bmp copiefinale  //avec copiefinale le nom du fichier que l'on souhaite donner à la copie qu'on va créer




