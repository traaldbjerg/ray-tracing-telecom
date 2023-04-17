#include "distance.hpp"

void compute_distance(Ray &ray) {
    std::vector<std::vector<double>> path = ray.get_path();
    double distance = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        std::vector<double> ray_segment = {path[i + 1][0] - path[i][0], path[i + 1][1] - path[i][1]};
        distance += sqrt(ray_segment[0]*ray_segment[0] + ray_segment[1]*ray_segment[1]);
    }
    ray.add_loss_factor(1/distance);
}