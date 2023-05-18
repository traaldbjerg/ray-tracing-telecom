#include "antenna.hpp"
#include "setup.hpp"

Antenna::Antenna(std::vector<double> t, int type) {
    position = t;
    this->type = type;
    if (type == 1) {
        power = 0.1; // P_TX
    }
    else if (type == 2) {
        power = 3.16227766; // P_TX
    }
    else if (type == 3) {
        power = 3.16227766; // P_TX
    }
    
}

Antenna::~Antenna() {} // destructeur

std::complex<double> Antenna::compute_directivity(double angle){ // retourne le gain
    std::complex<double> res;
    if (type == 3) {
        double g_max = 21.5836; // gain maximal en dB
        double delta = 0.1; // angle pour lequel a lieu le gain maximal DOIT ETRE COMPRIS ENTRE -PI et PI
        double phi_3dB = 0.523599; // angle pour lequel le gain est réduit de 3dB -> largeur du faisceau, ici 30 degrés en radians
        res = pow(10.0, (g_max - 12 * (angle - delta) / phi_3dB * (angle - delta) / phi_3dB ) / 10.0);
    }
    else {
        res = 1.7; // G_TX ou 1.7 ????
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

