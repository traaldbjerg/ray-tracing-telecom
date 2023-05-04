#include <vector>
#include <math.h>

double dotproduct(std::vector<double> u, std::vector<double> v); // produit scalaire

double normalised_dotproduct(std::vector<double> u, std::vector<double> v); // produit scalaire normalisé

double CCW(std::vector<double> a, std::vector<double> b, std::vector<double> c); // test de position d'un point par rapport à un segment

int intersect(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> d); // test d'intersection entre deux segments

double signed_acos(std::vector<double> u, std::vector<double> v); // acos qui renvoie l'angle signé