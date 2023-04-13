#include <vector>
#include <math.h>

double dotproduct(std::vector<double> u, std::vector<double> v);

double normalised_dotproduct(std::vector<double> u, std::vector<double> v);

double CCW(std::vector<double> a, std::vector<double> b, std::vector<double> c);

int intersect(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> d);