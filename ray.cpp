#include "ray.hpp"

Ray::Ray(std::vector<double> r) {loss_factors = {1}; path = {{r[0], r[1]}};} // constructeur

Ray::~Ray() {} // destructeur

void Ray::extend_path(std::vector<double> new_point) { // rajoute un point à la liste des points du rayon
    path.push_back(new_point);
}

std::vector<std::vector<double>> Ray::get_path() { // retourne l'ensemble des extrémités des segments du rayon
    return path;
}

std::vector<double> Ray::get_last_point() { // retourne le dernier point du rayon
    return path.back();
}

void Ray::add_loss_factor(double factor) { // rajouter un facteur de perte dans la liste
    loss_factors.push_back(factor);
}

double Ray::compute_power() { // calcule le facteur de perte total du rayon
    double loss = 1;
    for (int i = 0; i < loss_factors.size(); i++) {
        loss *= loss_factors[i];
    }
    return fabs(loss); // fabs pour float et pas abs qui traite les int
}

void Ray::print_path() { // debug
    for (int i = 0; i < path.size(); i++) {
        std::cout << "Point " << i << ": (" << path[i][0] << ", " << path[i][1] << ")" << std::endl; // debug
    }
}

void Ray::print_loss_factors() {
    std::cout << "Loss factors : ";
    for (int i = 0; i < loss_factors.size(); i++) {
        std::cout << loss_factors[i] << " ";
    }
    std::cout << std::endl;
}

void Ray::print_path_to_file(FILE *f) { // écrit l'ensemble des extrémités des segments du rayon dans le fichier f, pour plotter avec gnuplot
    for (int i = 0; i < path.size(); i++) {
        fprintf(f, "%f, %f\n", path[i][0], path[i][1]);
    }
    fprintf(f, "\n");
}