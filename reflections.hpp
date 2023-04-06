#include "common.hpp"
#include "dotproduct.hpp"
#include <iostream>
#include <math.h>

std::vector<double> compute_reflections(FILE f, std::vector<Wall> layout, std::vector<double> t, std::vector<double> r, int rec_depth, double &d);