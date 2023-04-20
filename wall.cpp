#include "wall.hpp"
#include <iostream>


Wall::Wall(double ux, double uy, double vx, double vy, int t) { // constructeur
    u.push_back(ux); // compo x
    u.push_back(uy); // compo y
    v.push_back(vx); // compo x
    v.push_back(vy); // compo y
    w.push_back(vx - ux); // compo x
    w.push_back(vy - uy); // compo y
    n.push_back(uy - vy); // compo x
    n.push_back(vx - ux); // compo y
    double norm_n = sqrt(n[0] * n[0] + n[1] * n[1]); n[0] /= norm_n; n[1] /= norm_n; // normalisation 
    type = t;
    // initialiser les différentes caractéristiques du mur
    if (type == 1) {width = 0.3 ; eps_rel = 4.6 ; sigma = 0.02;} // [m; -; S] // mur en brique
    else if (type == 2) {width = 0.5 ; eps_rel = 5.0 ; sigma = 0.014;} // [m; -; S] // mur en béton
    else if (type == 3) {width = 0.1 ; eps_rel = 2.25 ; sigma = 0.04;} // [m; -; S] // cloison
    else if (type == 4) {width = 0.15 ; eps_rel = 4.8 ; sigma = 0.018;} // [m; -; S] // mur de l'exo 8.1
    Z2 = sqrt(1.256e-6 / std::complex<double>(8.854e-12 * eps_rel, - sigma / OMEGA)); // espérons que la racine fonctionne comme on veut 
    //std::cout << "Z2 = " << Z2 << std::endl; // debug 
    gamma_propag = sqrt(std::complex<double>((-OMEGA) * (OMEGA) * 8.854e-12 * eps_rel * 1.256e-6, sigma * OMEGA * 1.256e-6));
    //std::cout << "gamma_propag = " << gamma_propag << std::endl; // debug
    

    // Z = sqrt(mu_0 / eps_0) / sqrt(eps_rel) par déf de la permittivité relative
    //   = 120 * M_PI / sqrt(eps_rel) en remplaçant les valeurs des constantes
}

//Wall::~Wall() {}

std::complex<double> Wall::getRcoef(double scal) { // coefficient de réflexion, on considère uniquement la polarisation perpendiculaire au plan d'incidence
    std::complex<double> gamma;
    double cosi = scal;   
    double cost = sqrt(1 - (1/eps_rel) * (1 - cosi*cosi)); // loi de Snell
    gamma = (Z2 * cosi - Z1 * cost) / (Z2 * cosi + Z1 * cost); // gamma perpendiculaire
    double s = width / cost;
    gamma = gamma - (1.0 - gamma * gamma) * (gamma * exp(-2.0 * gamma_propag * s) * exp(std::complex<double>(0, OMEGA/CELERITY * 2 * s * sqrt(1 - cosi * cosi) * sqrt(1 - cost * cost))))
        / (1.0 - gamma * gamma * exp(-2.0 * gamma_propag * s) * exp(std::complex<double>(0, OMEGA/CELERITY * 2 * s * sqrt(1 - cosi * cosi) * sqrt(1 - cost * cost)))); // calcul complet du coefficient
    return gamma;
}

std::complex<double> Wall::getTcoef(double scal) { // coefficient de transmission, on considère uniquement la polarisation perpendiculaire au plan d'incidence
    std::complex<double> T;
    double cosi = scal;   
    double cost = sqrt(1 - (1/eps_rel) * (1 - cosi*cosi)); // loi de Snell
    double s = width / cost;
    T = (Z2 * cosi - Z1 * cost) / (Z2 * cosi + Z1 * cost); // gamma perpendiculaire
    T = (1.0 - T * T) * exp(-gamma_propag * s)
        / (1.0 - T * T * exp(-2.0 * gamma_propag * s) * exp(std::complex<double>(0, OMEGA/CELERITY * 2 * s * sqrt(1 - cosi * cosi) * sqrt(1 - cost * cost)))); // calcul complet du coefficient
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
    fprintf(f, "%f, %f\n%f, %f\n\n\n", u[0], u[1], v[0], v[1]);
}
