#include "dotproduct.hpp"

double dotproduct(std::vector<double> u, std::vector<double> v) {
    double res = 0.0;
    res += u[0] * v[0];
    res += u[1] * v[1];
    return res;
}