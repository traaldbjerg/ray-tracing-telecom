#pragma once
#include <vector>
#include <math.h>
#include <iostream>

class Wall {
    // classe mur, reprend les propriétés des murs (position, épaisseur, permittivité, conductivité)
    // se charge également de donner le coefficient de réflexion et de transmission en fonction de l'angle d'incidence d'un rayon

    // attributs

    private:
    std::vector<double> u; // première extrémité du mur
    std::vector<double> v; // 2e extrémité du mur
    std::vector<double> n; // normale au mur
    std::vector<double> w; // vecteur directeur du mur
    int type; // 1 -> brique avec 30cm d'épaisseur ; 2 -> béton avec 50 cm d'épaisseur; 3 -> cloison avec 10 cm d'épaisseur
              // les valeurs de permittivité et de conductivité seront adaptées en fonction
    double width;
    double eps_rel;
    double sigma;

    // méthodes
    
    public:
    Wall(double ux, double uy, double vx, double vy, int t);
    //~Wall();
    double getRcoef(double scal);
    double getTcoef(double scal);
    std::vector<double> getU();
    std::vector<double> getV();
    std::vector<double> getW();
    std::vector<double> getN();
    int getType();
    void print_wall_to_file(FILE *f);

};
