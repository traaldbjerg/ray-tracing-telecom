#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>

class Antenna {
    // classe antenne, reprend les propriétés des rayons (extrémités des segments, facteurs de perte)

    // attributs
    private:
        int type;
        std::vector<double> position;
        double power;
    
    // méthodes
    public:
        Antenna(std::vector<double> t, int type); // constructeur
        ~Antenna(); // destructeur
        std::complex<double> compute_directivity(double angle); // calcule la directivité de l'antenne
        int get_type(); // retourne le type de l'antenne
        double get_P_TX(); // retourne la puissance d'émission de l'antenne
        double get_G_TX(); // retourne le gain d'émission de l'antenne
        std::vector<double> get_position(); // retourne la position de l'antenne
};

