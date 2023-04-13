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
    double norm_n = sqrt(n[0] * n[0] + n[1] * n[1]); n[0] /= norm_n; n[1] /= norm_n; // normalisation
    type = t;
    // initialiser les différentes caractéristiques du mur
    if (type == 1) {width = 0.3 ; eps_rel = 4.6 ; sigma = 0.02;} // [m; -; S]
    if (type == 2) {width = 0.5 ; eps_rel = 5.0 ; sigma = 0.014;} // [m; -; S]
    if (type == 3) {width = 0.1 ; eps_rel = 2.25 ; sigma = 0.04;} // [m; -; S]

    // Z = sqrt(mu_0 / eps_0) / sqrt(eps_rel) par déf de la permittivité relative
    //   = 120 * M_PI / sqrt(eps_rel) en remplaçant les valeurs des constantes
}

Wall::~Wall() {}

double Wall::getRcoef(double scal) { // coefficient de réflexion, on considère uniquement la polarisation perpendiculaire au plan d'incidence
    double gamma;
    double Z1 = 120 * M_PI;
    double Z2 = 120 * M_PI / sqrt(eps_rel);
    double cost = scal; // incorrect, loi de Snell
    double cosi = scal;
    gamma = (Z2 * cosi - Z1 * cost) / (Z2 * cosi + Z1 * cost);
    return gamma;
}

double Wall::getTcoef(double scal) { // coefficient de transmission, on considère uniquement la polarisation perpendiculaire au plan d'incidence
    double T;
    double Z1 = 120 * M_PI;
    double Z2 = 120 * M_PI / sqrt(eps_rel);
    double cost = scal; // incorrect, loi de Snell
    double cosi = scal;
    T = (2 * Z2 * cosi) / (Z2 * cosi + Z1 * cost);
    return T;
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