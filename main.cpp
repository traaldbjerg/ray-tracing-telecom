#include <iostream>
#include <chrono>
#include <cmath>
#include "common.hpp"
#include "reflections.hpp"

int main() {

    std::cout << "hello this is main" << std::endl;
    
    // variables à fixer
    int h = 10; // nombre de pas par mètre
    double Lx = 10.0;
    double Ly = 10.0;
    double power = 0.0;
    std::vector<double> t(2); t[0] = -5.0 ; t[1] = 5.0; // coordonnées de l'émetteur
    int recursion_depth = 2; // nombre de fois qu'on effectue la récursion
    std::vector<Wall> layout; // vecteur qui contiendra l'ensemble des murs
    std::vector<Ray> rays; // vecteur qui contiendra l'ensemble des rayons
    // initialiser layout
    std::cout << "hello" << std::endl;
    //layout.emplace_back(0.0, 0.0, 10.0, 0.0, 2);
    //layout.emplace_back(0.0, 0.0, 0.0, 10.0, 2);
    //layout.emplace_back(0.0, 10.0, 10.0, 10.0, 2);
    //layout.emplace_back(10.0, 0.0, 10.0, 10.0, 2);
    std::cout << "hello x2" << std::endl;
    Wall wall1(0.0, 0.0, 10.0, 0.0, 2); //layout.push_back(wall1);
    Wall wall2(0.0, 0.0, 0.0, 10.0, 2); //layout.push_back(wall2);
    Wall wall3(0.0, 10.0, 10.0, 10.0, 2); //layout.push_back(wall3);
    Wall wall4(10.0, 0.0, 10.0, 10.0, 2); //layout.push_back(wall4);
    std::cout << "hello x3" << std::endl;

    std::vector<double> r(2); // coordonées du récepteur, changera pour chaque itération de la boucle ci-dessous

    //int q = layout.size(); // nombre de murs

    FILE *f_rays = fopen("rays.dat", "w");
    FILE *f_power = fopen("power.dat", "w");

    //std::vector<double> r_copy = r; // copie de r pour pouvoir l'utiliser dans les fonctions

    // fonctions à appeler

    // boucle pour un récepteur unique, tracer les rayons

    for (int k = 1; k < recursion_depth; k++) { // d'abord transmission directe, puis 1 interaction puis 2 etc
        compute_reflections(*f_rays, layout, t, r, k, power, rays);

        // vérifier quels rayons sont acceptables, et les tracer

        
    }

    fclose(f_rays);

    // boucle pour toutes les positions de récepteur, plotter la puissance sur une grille

    for (int i = 0; i <= Lx * h; i++) { // itère d'abord verticalement, colonne par colonne
        r[0] = i/h;
        for(int j = 0 ; j < Ly * h ; j++) {
            r[1] = j/h;
            for (int k = 1; k < recursion_depth; k++) { // d'abord transmission directe, puis 1 interaction puis 2 etc
                compute_reflections(*f_power, layout, t, r, k, power, rays);
            }
        }
    }

    fclose(f_power);



    // résultats à sortir (gnuplot?)

    



}