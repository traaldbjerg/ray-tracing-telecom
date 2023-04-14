#include "wall.hpp"
#include <iostream>

//class Wall {
//attributes
/*std::vector<double> u; // première extrémité du mur
std::vector<double> v; // 2e extrémité du mur
std::vector<double> n; // normale au mur
int type; // 1 -> brique avec 30cm d'épaisseur ; 2 -> béton avec 50 cm d'épaisseur; 3 -> cloison avec 10 cm d'épaisseur
            // les valeurs de permittivité et de conductivité seront adaptées en fonction

public:*/
Wall::Wall(double ux, double uy, double vx, double vy, int t) {
    u.push_back(ux); // compo x
    u.push_back(uy); // compo y
    v.push_back(vx); // compo x
    v.push_back(vy); // compo y
    w.push_back(vx - ux); // compo x
    w.push_back(vy - uy); // compo y
    n.push_back(uy - vy); // compo x
    n.push_back(vx - ux); // compo y

    double norm_n = sqrt(n[0] * n[0] + n[1] * n[1]); n[0] /= norm_n; n[1] /= norm_n; // normalisation

    //std::cout << "normal:" << n[0] << ", " << n[1] << std::endl;
    type = t;
    // initialiser les différentes caractéristiques du mur
    if (type == 1) {width = 0.3 ; eps_rel = 4.6 ; sigma = 0.02;} // [m; -; S]
    if (type == 2) {width = 0.5 ; eps_rel = 5.0 ; sigma = 0.014;} // [m; -; S]
    if (type == 3) {width = 0.1 ; eps_rel = 2.25 ; sigma = 0.04;} // [m; -; S]

    // Z = sqrt(mu_0 / eps_0) / sqrt(eps_rel) par déf de la permittivité relative
    //   = 120 * M_PI / sqrt(eps_rel) en remplaçant les valeurs des constantes
}

//Wall::~Wall() {}

double Wall::getRcoef(double scal) { // coefficient de réflexion, on considère uniquement la polarisation perpendiculaire au plan d'incidence
    double gamma;
    double Z1 = 120 * M_PI;
    double Z2 = 120 * M_PI / sqrt(eps_rel);
    double cosi = scal;   
    double cost = sqrt( (1/eps_rel) * (1 + cosi*cosi) - 1 ); // loi de Snell
    gamma = (Z2 * cosi - Z1 * cost) / (Z2 * cosi + Z1 * cost);
    return gamma;
}

double Wall::getTcoef(double scal) { // coefficient de transmission, on considère uniquement la polarisation perpendiculaire au plan d'incidence
    double T;
    double Z1 = 120 * M_PI;
    double Z2 = 120 * M_PI / sqrt(eps_rel);
    double cosi = scal;   
    double cost = sqrt( (1/eps_rel) * (1 + cosi*cosi) - 1 ); // loi de Snell
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

void Wall::print_wall_to_file(FILE *f) {
    fprintf(f, "%f, %f\n%f, %f\n\n", u[0], u[1], v[0], v[1]);
}

//};