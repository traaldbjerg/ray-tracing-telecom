#include "reflections.hpp"

std::vector<double> compute_reflections(FILE f, std::vector<Wall> layout, std::vector<double> t, std::vector<double> r,
 int rec_depth, double &d, std::vector<Ray> &rays) {
    // layout ensemble des murs du plan ; r les coordonnées du récepteur
    // trouver les n-uples de murs qui permettent les réflexions successives jusqu'au récepteur
    // retourne un vecteur de double, les 2 premières composantes sont les coordonnées de l'émetteur virtuel et le 3e est la perte de puissance

    //std::vector<std::vector<double>> reflections(n); // vecteur qui contiendra les coordonnées des émetteurs virtuels

    //std::vector<std::vector<double>> reflections(n);

    for (int i = 0; i < layout.size() ; i++) { // itère sur les murs

        std::vector<Ray> rays_in_scope;

        //std::vector<double> loss_factors;

        // trouver les positions du récepteur et de l'émetteur (virtuel ou non) par rapport au mur

        std::vector<std::vector<double>> previous_t; // coordonnées des émetteurs virtuels précédents (pour la récursion)
        previous_t.push_back(t); // ajouter l'émetteur réel à la liste des émetteurs virtuels précédents

        std::vector<double> r_rel(2);
        r_rel[0] = layout[i].getU()[0] - r[0];  // vecteur de r à u
        r_rel[1] = layout[i].getU()[1] - r[1]; 
        std::vector<double> t_rel(2);
        t_rel[0] = layout[i].getU()[0] - t[0];  // vecteur de t à u
        t_rel[1] = layout[i].getU()[1] - t[1]; 

        std::vector<double> t_virtuel(2);
        t_virtuel[0] = t[0] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[0];
        t_virtuel[1] = t[1] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[1];

        previous_t.push_back(t_virtuel); // ajouter l'émetteur virtuel à la liste des émetteurs virtuels précédents

        // vérifier si le point de réflexion n'est pas en dehors du mur

        //std::vector<double> diff(2); diff[0] = r[0] - t_virtuel[0]; diff[1] = r[1] - t_virtuel[1];
        //double dist = (diff[1] * (r[0] - layout[i].getU()[0]) - diff[0] * (r[1] - layout[i].getU()[1])) / (layout[i].getW()[0] * diff[1] - layout[i].getW()[1] * diff[0]);
                                                                                                        // division par 0 ssi rayon parallèle au mur

        //if (0.0 < dist && dist < 1.0) { // sinon la réflexion est invalide car en dehors du mur -> pas besoin de calculer plus de choses

        std::vector<double> r_copy = r; // copie de r pour la récursion qui peut être modifiée par l'itération suivante
            
        if (rec_depth > 1) {
            compute_reflections(f, layout, t_virtuel, r_copy, rec_depth - 1, d, rays_in_scope); // récursion
        } else {
            Ray new_ray = Ray();
            rays_in_scope.push_back(new_ray);
            new_ray.extend_path(r);
        }

        for (int j = 1; j < rays_in_scope.size(); j++) { // traiter chaque rayon qui arrive au mur individuellement

            std::vector<double> r_copy = rays_in_scope[j].get_last_point(); // copie de r pour la récursion qui peut être modifiée par l'itération suivante

            std::vector<double> diff(2); diff[0] = r_copy[0] - t_virtuel[0]; diff[1] = r_copy[1] - t_virtuel[1];
            double dist = (diff[1] * (r_copy[0] - layout[i].getU()[0]) - diff[0] * (r_copy[1] - layout[i].getU()[1])) / (layout[i].getW()[0] * diff[1] - layout[i].getW()[1] * diff[0]);
                                                                                                            // division par 0 ssi rayon parallèle au mur

            if (0.0 < dist && dist < 1.0 // sinon la réflexion est invalide car en dehors du mur -> pas besoin de calculer plus de choses
                        && dotproduct(t_virtuel, layout[i].getN()) * dotproduct(r_copy, layout[i].getN()) < 0.0) { 
                        // si l'antenne virtuelle est du côté opposé au récepteur -> réflexion

                std::vector<double> r_copy_2 = r_copy; // point de réflexion de l'itération précédente
                r_copy[0] = layout[i].getU()[0] + dist * layout[i].getW()[0]; // calculer le point de réflexion de cette itération-ci
                r_copy[1] = layout[i].getU()[1] + dist * layout[i].getW()[1];

                std::vector<double> ray_segment(2); ray_segment[0] = r_copy_2[0] - r_copy[0]; ray_segment[1] = r_copy_2[1] - r_copy[1];

                rays_in_scope[j].extend_path(r_copy);
                rays_in_scope[j].add_loss_factor(layout[i].getRcoef(normalised_dotproduct(ray_segment, layout[i].getN())));
            }

                // calculer la somme de puissance ici -> laisser une méthode de Wall donner les coefs de réflexion et de transmission?

                //loss_factors.push_back(layout[i].getRcoef(normalised_dotproduct(ray_segment, layout[i].getN()))); // obtenir le coefficient de perte par réflexion

            else { // rebond invalide -> retirer le rayon de la liste des rayons à traiter
                rays_in_scope.erase(rays_in_scope.begin() + j);
                j--;
            }
        
        }

        for (int j = 0; j < rays_in_scope.size(); j++) { // ajouter les rayons à la liste des rayons qui sera fournie au scope supérieur
                rays.push_back(rays_in_scope[j]);
            }

        //}
        /*}
        else { // transmission

            // calculer la perte de puissance ici
            if (rec_depth > 1) compute_reflections(f, layout, t, r, rec_depth - 1, d); // récursion
        }*/
    }
 }