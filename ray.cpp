#include "ray.hpp"

Ray::Ray(std::vector<double> r) {loss_factors = {1}; path = {{r[0], r[1]}};}

Ray::~Ray() {}

void Ray::extend_path(std::vector<double> new_point) {
    path.push_back(new_point);
}

std::vector<std::vector<double>> Ray::get_path() {
    return path;
}

void Ray::add_loss_factor(double factor) {
    loss_factors.push_back(factor);
}

std::vector<double> Ray::get_last_point() {
    return path.back();
}

void Ray::print_path() {
    for (int i = 0; i < path.size(); i++) {
        std::cout << "Point " << i << ": (" << path[i][0] << ", " << path[i][1] << ")" << std::endl;
    }
}

/*void Ray::print_loss_factors() {
    for (int i = 0; i < loss_factors.size(); i++) {
        std::cout << "Loss factor " << i << ": " << loss_factors[i] << std::endl;
    }
}*/

void Ray::print_path_to_file(FILE *f) {
    for (int i = 0; i < path.size(); i++) {
        //f << path[i][0] << " " << path[i][1] << std::endl;
        fprintf(f, "%f, %f\n", path[i][0], path[i][1]);
    }
    fprintf(f, "\n");
}