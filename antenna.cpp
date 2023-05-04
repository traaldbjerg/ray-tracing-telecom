#include "antenna.hpp"

Antenna::Antenna(std::vector<double> t, int type) {
    position = t;
    this->type = type;
    if (type == 1) {
        power = 0.1; // P_TX
    }
    else if (type == 2) {
        power = 3.16; // P_TX
    }
    else if (type == 3) {
        power = 3.16; // P_TX
    }
    
}

Antenna::~Antenna() {} // destructeur

double Antenna::compute_directivity(double angle){ // retourne le gain
    double res;
    if (type == 3) {
        double g_max = 1.0; // gain maximal en dB
        double delta = 0.3490659; // angle pour lequel a lieu le gain maximal, 20 degrés en radians
        double phi_3dB = 0.3490659; // angle pour lequel le gain est réduit de 3dB -> largeur du faisceau
        res = pow(10, (g_max - 12 * (angle - delta) / phi_3dB * (angle - delta) / phi_3dB ) / 10);
    }
    else {
        res = 1.0; // G_TX
    }
    return res;
}

double Antenna::get_P_TX() {
    return power;
}

double Antenna::get_G_TX() { // un peu inutile mais pour rester cohérent
    return 1.0;
}

int Antenna::get_type() {
    return type;
}

std::vector<double> Antenna::get_position() {
    return position;
}

