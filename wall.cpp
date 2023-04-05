#include "wall.hpp"

//class Wall {
//attributes
/*std::vector<double> u; // première extrémité du mur
std::vector<double> v; // 2e extrémité du mur
std::vector<double> n; // normale au mur
int type; // 1 -> brique avec 30cm d'épaisseur ; 2 -> béton avec 50 cm d'épaisseur; 3 -> cloison avec 10 cm d'épaisseur
            // les valeurs de permittivité et de conductivité seront adaptées en fonction

public:*/
Wall::Wall(double ux, double uy, double vx, double vy, int t) {
    u[0] = ux;
    u[1] = uy;
    v[0] = vx;
    v[1] = vy;
    w[0] = vx - ux;
    w[1] = vy - uy;
    n[0] = uy - vy;
    n[1] = vx - ux;
    double norm_n = sqrt(n[0] * n[0] + n[1] * n[1]); n[0] /= norm_n; n[1] /= norm_n; //normalisation
    type = t;
    // initialiser les différentes caractéristiques du mur
    if (type == 1) {width = 0.3 ; rel_eps = 4.6 ; sigma = 0.02;}
    if (type == 2) {width = 0.5 ; rel_eps = 5.0 ; sigma = 0.014;}
    if (type == 3) {width = 0.1 ; rel_eps = 2.25 ; sigma = 0.04;}
}

Wall::~Wall() {}

double Wall::getRcoef() {
    
}

double Wall::getTcoef() {
    
}

std::vector<double> Wall::getU() {
    return u;
}

std::vector<double> Wall::getV() {
    return v;
}

std::vector<double> Wall::getN() {
    return n;
}

std::vector<double> Wall::getW() {
    return w;
}

int Wall::getType() {
    return type;
}

//};