#include "ray.hpp"

Ray::Ray(std::vector<double> r) {loss_factors = {1}; path = {{r[0], r[1]}}; walls_hit = {100};} // constructeur, 100 en placeholder

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

void Ray::add_loss_factor(std::complex<double> factor) { // rajouter un facteur de perte dans la liste
    loss_factors.push_back(factor);
}

void Ray::add_loss_factor(double factor) { // rajouter un facteur de perte dans la liste
    loss_factors.push_back(factor);
}

std::complex<double> Ray::compute_field() { // calcule le facteur de perte total du rayon
    std::complex<double> loss = 1;
    for (int i = 0; i < loss_factors.size(); i++) {
        loss *= loss_factors[i];
    }
    return loss; // fabs pour float et pas abs qui traite les int
}

void Ray::add_wall_hit(int wall_index) { // rajoute un mur dans la liste des murs touchés, permet de ne pas vérifier les intersections avec des murs déjà touchés lorsqu'on cherche les transmissions
    walls_hit.push_back(wall_index);
}

std::vector<int> Ray::get_walls_hit() { // retourne la liste des murs touchés par le rayon
    return walls_hit;
}

//void Ray::add_all_loss_factors(std::vector<Wall> &layout) { // rajoute tous les facteurs de perte d'un vecteur dans la liste des facteurs de perte du rayon
//    for (int i = 0; i < walls_hit.size(); i++) {
//        this.add_loss_factor(layout[i].getRcoef(normalised_dotproduct(ray_segment, layout[i].getN())));
//    }
//}

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

void Ray::print_walls_hit() {
    std::cout << "Walls hit : ";
    for (int i = 0; i < walls_hit.size(); i++) {
        std::cout << walls_hit[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<double> Ray::get_last_segment() {
    std::vector<double> last_segment = {path[path.size()-2][0] - path[path.size()-1][0], path[path.size()-2][1] - path[path.size()-1][1]};
    return last_segment;
}