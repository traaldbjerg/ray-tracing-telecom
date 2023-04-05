#pragma once
#include <vector>
#include <math.h>

class Wall {

    private:
    std::vector<double> u; // première extrémité du mur
    std::vector<double> v; // 2e extrémité du mur
    std::vector<double> n; // normale au mur
    std::vector<double> w; // vecteur directeur du mur
    int type; // 1 -> brique avec 30cm d'épaisseur ; 2 -> béton avec 50 cm d'épaisseur; 3 -> cloison avec 10 cm d'épaisseur
              // les valeurs de permittivité et de conductivité seront adaptées en fonction
    double width;
    double rel_eps;
    double sigma;

    
    public:
    Wall(double ux, double uy, double vx, double vy, int t);
    ~Wall();
    double getRcoef();
    double getTcoef();
    std::vector<double> getU();
    std::vector<double> getV();
    std::vector<double> getW();
    std::vector<double> getN();
    int getType();

};
