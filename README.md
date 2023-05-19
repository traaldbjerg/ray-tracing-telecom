# ray-tracing-telecom

Projet de Ray-Tracing pour le cours ELEC-H304 à l'Ecole Polytechnique de Bruxelles

## Dépendances

Gnuplot, Linux

## Fonctionnement

Lancer le main fera tourner le programme. 

Les différentes constantes (comme la fréquence de l'onde monochromatique) sont réglées dans setup.hpp. Pour changer la position des antennes ou le layout des murs, il faudra changer le début de main.cpp où tous les objets sont initialisés. Changer de mode de fonctionnement (mode de tracé des rayons ou mode heatmap) se fait en changeant la variable compute_power au début de main.cpp. On peut aussi y régler l'entier rec_depth, qui gère le nombre de réflexions maximal pour les rayons à calculer.

