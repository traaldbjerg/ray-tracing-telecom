#include <iostream>
#include <chrono>
#include <cmath>
#include "common.hpp"
#include "reflections.hpp"

int main() {

    //std::cout << "hello this is main" << std::endl;
    
    // variables à fixer
    int h = 10; // nombre de pas par mètre
    //double Lx = 10.0;
    //double Ly = 10.0;
    double power = 0.0;
    //std::vector<double> t(2); t[0] = 32 ; t[1] = 10; // coordonnées de l'émetteur
    //std::vector<double> r(2); r[0] = 47; r[1] = 65; // coordonnées du récepteur
    std::vector<double> t(2); t[0] = -5 ; t[1] = 5; // coordonnées de l'émetteur
    std::vector<double> r(2); r[0] = 5; r[1] = 5; // coordonnées du récepteur
    int recursion_depth = 10; // nombre de fois qu'on effectue la récursion
    std::vector<Wall> layout; // vecteur qui contiendra l'ensemble des murs
    std::vector<Ray> rays; // vecteur qui contiendra l'ensemble des rayons
    // initialiser layout
    //std::cout << "hello" << std::endl;
    //layout.emplace_back(0.0, 0.0, 10.0, 0.0, 2);
    //layout.emplace_back(0.0, 0.0, 0.0, 10.0, 2);
    //layout.emplace_back(0.0, 10.0, 10.0, 10.0, 2);
    //layout.emplace_back(10.0, 0.0, 10.0, 10.0, 2);
    //std::cout << "hello x2" << std::endl;
    // disposition de l'exo 8.1
    //Wall wall1(0.0, 0.0, 0.0, 80.0, 2); layout.push_back(wall1);
    //Wall wall2(0.0, 20.0, 80.0, 20.0, 2); layout.push_back(wall2);
    //Wall wall3(0.0, 80.0, 80.0, 80.0, 2); layout.push_back(wall3);
    Wall wall1(0.0, 0.0, 0.0, 10.0, 2); layout.push_back(wall1);
    Wall wall2(0.0, 0.0, 10.0, 0.0, 2); layout.push_back(wall2);
    Wall wall3(0.0, 10.0, 10.0, 10.0, 2); layout.push_back(wall3);
    Wall wall4(10.0, 0.0, 10.0, 10.0, 2); layout.push_back(wall4);
    //Wall wall5(4, 3, 6, 5, 2); layout.push_back(wall5);
    //std::cout << "hello x3" << std::endl;
    
    
    //int q = layout.size(); // nombre de murs

    FILE *f_rays = fopen("rays.dat", "w");
    FILE *f_walls = fopen("walls.dat", "w");
    FILE *f_power = fopen("power.dat", "w");

    // placer les murs dans le fichier correspondant

    for (int i = 0; i < layout.size(); i++) {
        layout[i].print_wall_to_file(f_walls);
    }

    fclose(f_walls);

    // fonctions à appeler

    // boucle pour un récepteur unique, tracer les rayons

    for (int k = recursion_depth; k > 0; k--) { // d'abord max de réflexions puis ... puis 1 interaction puis 0 etc
        compute_reflections(*f_rays, layout, 100, t, r, k, power, rays); // 100 en placeholder, fonctionne tant qu'il y a moins de 100 murs
    }

    // vérifier quels rayons sont acceptables, et les tracer

    Ray direct_ray(r); direct_ray.extend_path(t); rays.push_back(direct_ray); // rajouter le rayon direct

    for (int i = 0; i < rays.size(); i++) {
        rays[i].extend_path(t); // rajouter l'émetteur à la liste des points du rayon
        rays[i].print_path();
        rays[i].print_path_to_file(f_rays);
    }



    fclose(f_rays);

    // boucle pour toutes les positions de récepteur, plotter la puissance sur une grille
/*
    for (int i = 0; i <= Lx * h; i++) { // itère d'abord verticalement, colonne par colonne
        r[0] = i/h;
        for(int j = 0 ; j < Ly * h ; j++) {
            r[1] = j/h;
            for (int k = 1; k < recursion_depth; k++) { // d'abord transmission directe, puis 1 interaction puis 2 etc
                compute_reflections(*f_power, layout, t, r, k, power, rays);
            }
        }
    }
*/
    fclose(f_power);



    // résultats à sortir (gnuplot?)

    system("gnuplot -persist \"lines.gnu\"");

    



}