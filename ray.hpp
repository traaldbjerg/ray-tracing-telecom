#pragma once
#include <vector>
#include <iostream>

class Ray {
    private:
        std::vector<std::vector<double>> path;
        std::vector<double> loss_factors;
    public:
        Ray(std::vector<double> r);
        ~Ray();
        void add_loss_factor(double factor);
        std::vector<double> get_last_point();
        void extend_path(std::vector<double> new_point);
        std::vector<std::vector<double>> get_path();
        void print_path();
};
