#include <iostream>
#include <chrono>
#include <cmath>
#include "common.hpp"
#include "reflections.hpp"



int main() {
    
    // variables à fixer
    int h = 10; // nombre de pas par mètre
    double Lx = 10.0;
    double Ly = 10.0;
    double power = 0.0;
    std::vector<double> t(2); t[0] = -5.0 ; t[1] = 5.0; // coordonnées de l'émetteur
    int recursion_depth = 2; // nombre de fois qu'on effectue la récursion
    std::vector<Wall> layout(4); // vecteur qui contiendra l'ensemble des murs
    // initialiser layout
    layout.push_back(Wall(0.0, 0.0, 10.0, 0.0, 2));
    layout.push_back(Wall(0.0, 0.0, 0.0, 10.0, 2));
    layout.push_back(Wall(0.0, 10.0, 10.0, 10.0, 2));
    layout.push_back(Wall(10.0, 0.0, 10.0, 10.0, 2));

    std::vector<double> r(2);

    FILE *f_rays = fopen("rays.dat", "w");
    FILE *f_power = fopen("power.dat", "w");





    // fonctions à appeler

    for (int i = 0; i <= Lx * h; i++) {
        r[0] = i/h;
        for(int j = 0 ; j < Ly * h ; j++) {
            r[1] = j/h;
            for (int k = 1; k < recursion_depth; k++) { // d'abord transmission directe, puis 1 interaction puis 2 etc
            compute_reflections(*f_rays, layout, t, r, k, power);
            }
        }
    }

    fclose(f_rays);
    fclose(f_power);



    // résultats à sortir (gnuplot?)





}