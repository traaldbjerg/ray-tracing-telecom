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
    std::vector<Wall> layout; // vecteur qui contiendra l'ensemble des murs
    // initialiser layout
    layout.push_back(Wall(0.0, 0.0, 10.0, 0.0, 2));
    layout.push_back(Wall(0.0, 0.0, 0.0, 10.0, 2));
    layout.push_back(Wall(0.0, 10.0, 10.0, 10.0, 2));
    layout.push_back(Wall(10.0, 0.0, 10.0, 10.0, 2));

    std::vector<double> r(2); // coordonées du récepteur, changera pour chaque itération de la boucle ci-dessous

    int q = layout.size(); // nombre de murs

    FILE *f_rays = fopen("rays.dat", "w");
    FILE *f_power = fopen("power.dat", "w");

    std::vector<double> &r_copy = r; // copie de r pour pouvoir l'utiliser dans les fonctions

    // fonctions à appeler

    // boucle pour un récepteur unique, tracer les rayons

    for (int k = 1; k < recursion_depth; k++) { // d'abord transmission directe, puis 1 interaction puis 2 etc
        int n = 0; // nombre de réflexions potentielles
        for (int a = 1; a < k; a++) {
            int m = 1;
            for(int l = 0; l < a; l++) m *= q;
            n += m; // ... + q^4 + q^3 + q^2 + q
        }
        double *loss_factors = new double[n]; // vecteur qui contiendra les facteurs de perte de puissance
        double *reflections = new double[2 * n]; // vecteur qui contiendra les coordonnées des points de réflexion successifs 
        compute_reflections(*f_rays, layout, t, r, k, power, loss_factors, reflections);

        // vérifier quels rayons sont acceptables, et les tracer


    }

    fclose(f_rays);

    // boucle pour toutes les positions de récepteur, plotter la puissance sur une grille

    for (int i = 0; i <= Lx * h; i++) { // itère d'abord verticalement, colonne par colonne
        r[0] = i/h;
        for(int j = 0 ; j < Ly * h ; j++) {
            r[1] = j/h;
            for (int k = 1; k < recursion_depth; k++) { // d'abord transmission directe, puis 1 interaction puis 2 etc
                int n = 0; // nombre de réflexions potentielles
                for (int a = 1; a < k; a++) {
                    int m = 1;
                    for(int l = 0; l < a; l++) m *= q;
                    n += m; // ... + q^4 + q^3 + q^2 + q
                }
                double *loss_factors = new double[n]; // vecteur qui contiendra les facteurs de perte de puissance
                double *reflections = new double[2 * n]; // vecteur qui contiendra les coordonnées des points de réflexion successifs 
                compute_reflections(*f_power, layout, t, r, k, power, loss_factors, reflections);
            }
        }
    }

    fclose(f_power);



    // résultats à sortir (gnuplot?)

    



}