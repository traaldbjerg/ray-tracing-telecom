#include "reflections.hpp"

void compute_reflections(std::vector<Wall> &layout, int previous_wall_index, std::vector<double> t, std::vector<double> r,
 int remaining_rec_depth, std::vector<Ray> &rays) {

    // calcule les réflexions successives d'un rayon jusqu'au récepteur en récursion en partant du récepteur,
    // où toutes les combinaisons de murs instancient un rayon, puis remonte les couches de récursion en supprimant les rayons
    // qui ne sont pas associés à des combinaisons de murs possibles
    // layout ensemble des murs du plan ; previous_wall_index l'index du mur précédent (pour éviter 2 réflexions consécutives sur le même mur)
    // r les coordonnées du récepteur; t les coordonnées de l'émetteur (virtuel ou non); remaining_rec_depth profondeur de récursion;
    // rays ensemble des rayons
    // trouver les n-uples de murs qui permettent les réflexions successives jusqu'au récepteur

    for (int i = 0; i < layout.size() ; i++) { // itère sur les murs

        if (i == previous_wall_index) {} //{std::cout << "this is a jump" << std::endl;} // sauter le mur sur lequel on s'est reflété précédemment

        else {
            std::vector<Ray> rays_in_scope; // séparer l'ensemble complet de tous les rayons de ceux dans le scope de cette récursion-ci

            // trouver les positions du récepteur et de l'émetteur (virtuel ou non) par rapport au mur
            std::vector<double> r_rel(2);
            r_rel[0] = - layout[i].getU()[0] + r[0];  // vecteur de r à u
            r_rel[1] = - layout[i].getU()[1] + r[1]; 
            std::vector<double> t_rel(2);
            t_rel[0] = - layout[i].getU()[0] + t[0];  // vecteur de t à u
            t_rel[1] = - layout[i].getU()[1] + t[1]; 
            std::vector<double> t_virtuel(2); // coordonnées de l'émetteur virtuel
            t_virtuel[0] = t[0] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[0];
            t_virtuel[1] = t[1] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[1];
            std::vector<double> t_virtuel_rel(2); // coordonnées de l'émetteur virtuel par rapport au mur
            t_virtuel_rel[0] = t_virtuel[0] - layout[i].getU()[0];
            t_virtuel_rel[1] = t_virtuel[1] - layout[i].getU()[1];
                
            if (remaining_rec_depth > 1) {
                compute_reflections(layout, i, t_virtuel, r, remaining_rec_depth - 1, rays_in_scope); // récursion
            } else {
                Ray new_ray(r);
                rays_in_scope.push_back(new_ray);
            }

            for (int j = 0; j < rays_in_scope.size(); j++) { // traiter chaque rayon qui arrive au mur individuellement, et éliminer tous ceux qui correspondent à des combinaisons de murs impossibles

                std::vector<double> r_copy = rays_in_scope[j].get_last_point(); // copie de r pour la récursion qui peut être modifiée par l'itération suivante

                std::vector<double> r_copy_rel(2); // coordonnées de r par rapport au mur
                r_copy_rel[0] = - layout[i].getU()[0] + r_copy[0];  // vecteur de r à u
                r_copy_rel[1] = - layout[i].getU()[1] + r_copy[1];

                std::vector<double> diff(2); diff[0] = r_copy[0] - t_virtuel[0]; diff[1] = r_copy[1] - t_virtuel[1]; // trouver la position du point de réflexion
                double dist = (diff[1] * (r_copy[0] - layout[i].getU()[0]) - diff[0] * (r_copy[1] - layout[i].getU()[1])) / (layout[i].getW()[0] * diff[1] - layout[i].getW()[1] * diff[0]);
                                                                                                                // division par 0 ssi rayon parallèle au mur

                if (0.0 < dist && dist < 1.0 // sinon la réflexion est invalide car en dehors du mur -> pas besoin de calculer plus de choses
                            && dotproduct(t_virtuel_rel, layout[i].getN()) * dotproduct(r_copy_rel, layout[i].getN()) < 0.0
                            ) { 
                            // si l'antenne virtuelle est du côté opposé au récepteur -> réflexion valide

                    r_copy[0] = layout[i].getU()[0] + dist * layout[i].getW()[0]; // calculer le point de réflexion de cette itération-ci
                    r_copy[1] = layout[i].getU()[1] + dist * layout[i].getW()[1];

                    rays_in_scope[j].extend_path(r_copy);
                    rays_in_scope[j].add_wall_hit(i); // ajouter le mur à la liste des murs sur lesquels le rayon rebondit
                }

                else { // rebond invalide -> retirer le rayon de la liste des rayons à traiter
                    rays_in_scope.erase(rays_in_scope.begin() + j);
                    j--; // pour ne pas sauter un rayon puisque la liste est réduite de 1 après délétion
                }
            }
            for (int j = 0; j < rays_in_scope.size(); j++) { // ajouter les rayons à la liste des rayons qui sera fournie au scope supérieur
                    rays.push_back(rays_in_scope[j]);
                }
        }
    }
 }
