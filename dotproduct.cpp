#include "dotproduct.hpp"

double dotproduct(std::vector<double> u, std::vector<double> v) { // produit scalaire
    double res = 0.0;
    res += u[0] * v[0];
    res += u[1] * v[1];
    return res;
}

double normalised_dotproduct(std::vector<double> u, std::vector<double> v) { // donne le cosinus de l'angle entre les 2 vecteurs
    double res = 0.0;
    res += u[0] * v[0];
    res += u[1] * v[1];
    double norm = sqrt(u[0] * u[0] + u[1] * u[1]); res /= norm; norm = sqrt(v[0] * v[0] + v[1] * v[1]); res /= norm;
    return fabs(res);
}

// pompé de https://stackoverflow.com/questions/15311018/c-procedure-for-determining-whether-two-segments-intersect

double CCW(std::vector<double> a, std::vector<double> b, std::vector<double> c) // test de position d'un point par rapport à un segment
{ return (b[0]-a[0])*(c[1]-a[1]) - (b[1]-a[1])*(c[0]-a[0]); }

int intersect(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> d) // test d'intersection entre deux segments
// renvoie 1 si les segments [a,b] et [c,d] s'intersectent, 0 sinon
{ return (CCW(a,b,c)*CCW(a,b,d)<0 && CCW(c,d,b)*CCW(c,d,a)<0); }
