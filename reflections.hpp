#include "common.hpp"
#include "dotproduct.hpp"
#include <iostream>
#include <math.h>
#include "progressbar.hpp"

void compute_reflections(std::vector<Wall> layout, int last_wall_index, std::vector<double> t, std::vector<double> r,
 int rec_depth, std::vector<Ray> &rays);
