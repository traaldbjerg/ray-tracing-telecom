#include "ray.hpp"

Ray::Ray() {loss_factors = {1};}

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
    return path[path.size() - 1];
}

void Ray::print_path() {
    for (int i = 0; i < path.size(); i++) {
        std::cout << "Point " << i << ": (" << path[i][0] << ", " << path[i][1] << ")" << std::endl;
    }
}