#include "reflections.hpp"

std::vector<double> compute_reflections(std::vector<Wall> layout, std::vector<double> t, std::vector<double> r, int rec_depth, double &d) {
    // layout ensemble des murs du plan ; r les coordonnées du récepteur
    // trouver les n-uples de murs qui permettent les réflexions successives jusqu'au récepteur
    // retourne un vecteur de double, les 2 premières composantes sont les coordonnées de l'émetteur virtuel et le 3e est la perte de puissance
    for (int i = 0; i < layout.size() ; i++) {
        // trouver les positions du récepteur et de l'émetteur (virtuel ou non) par rapport au mur
        std::vector<double> r_rel(2);
        r_rel[0] = layout[i].getU()[0] - r[0];
        r_rel[1] = layout[i].getU()[1] - r[1];
        std::vector<double> t_rel(2);
        t_rel[0] = layout[i].getU()[0] - t[0];
        t_rel[1] = layout[i].getU()[1] - t[1];
        // vérifier s'ils sont du même côté du mur

        if (dotproduct(t_rel, r_rel) > 0.0) { // réflexion
            std::vector<double> t_virtuel(2);
            t_virtuel[0] = t[0] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[0];
            t_virtuel[1] = t[1] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[1];

            // vérifier si le point de réflexion n'est pas en dehors du mur

            std::vector<double> diff(2); diff[0] = r[0] - t_virtuel[0]; diff[1] = r[1] - t_virtuel[1];
            double dist = (diff[1] * (r[0] - layout[i].getU()[0]) - diff[0] * (r[1] - layout[i].getU()[1])) / (layout[i].getW()[0] * diff[1] - layout[i].getW()[1] * diff[0]);
                                                                                                            // division par 0 ssi rayon parallèle au mur

            if (0.0 < dist && dist < 1.0) { // sinon la réflexion est invalide car en dehors du mur -> pas besoin de calculer plus

                // calculer la perte de puissance ici -> laisser une méthode de Wall donner les coefs de réflexion et de transmission?

                /*double add_dist = 0.0;
                add_dist += (r[0] - t_virtuel[0]) * (r[0] - t_virtuel[0]);
                add_dist += (r[1] - t_virtuel[1]) * (r[1] - t_virtuel[1]);
                add_dist = sqrt(add_dist);
                d += add_dist;*/
                if (rec_depth > 1) {
                    compute_reflections(layout, t_virtuel, r, rec_depth - 1, d); //
                }
            }
        }
        else { // transmission

            // calculer la perte de puissance ici
            if (rec_depth > 1) compute_reflections(layout, t, r, rec_depth - 1, d);
        }
    }
}
