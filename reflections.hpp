#include "common.hpp"
#include "dotproduct.hpp"
#include <math.h>

std::vector<double> compute_reflections(std::vector<Wall> layout, std::vector<double> t, std::vector<double> r, int rec_depth, double &d);