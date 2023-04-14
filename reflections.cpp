#include "reflections.hpp"

void compute_reflections(FILE f, std::vector<Wall> layout, int previous_wall_index, std::vector<double> t, std::vector<double> r,
 int rec_depth, double &d, std::vector<Ray> &rays) {

    //std::cout << "hello this is compute_reflections" << std::endl;
    // layout ensemble des murs du plan ; r les coordonnées du récepteur
    // trouver les n-uples de murs qui permettent les réflexions successives jusqu'au récepteur
    // retourne un vecteur de double, les 2 premières composantes sont les coordonnées de l'émetteur virtuel et le 3e est la perte de puissance

    for (int i = 0; i < layout.size() ; i++) { // itère sur les murs

        if (i == previous_wall_index) {} //{std::cout << "this is a jump" << std::endl;} // sauter le mur sur lequel on s'est reflété précédemment

        else {

            //std::cout << "this is wall " << i << std::endl;

            std::vector<Ray> rays_in_scope; // séparer l'ensemble complet de tous les rayons de ceux dans le scope de cette récursion-ci

            // trouver les positions du récepteur et de l'émetteur (virtuel ou non) par rapport au mur

            std::vector<double> r_rel(2);
            r_rel[0] = - layout[i].getU()[0] + r[0];  // vecteur de r à u
            r_rel[1] = - layout[i].getU()[1] + r[1]; 

            //std::cout << "r_rel " << i << ": (" << r_rel[0] << ", " << r_rel[1] << ")" << std::endl;
            std::vector<double> t_rel(2);
            t_rel[0] = - layout[i].getU()[0] + t[0];  // vecteur de t à u
            t_rel[1] = - layout[i].getU()[1] + t[1]; 

            //std::cout << "t_rel " << i << ": (" << t_rel[0] << ", " << t_rel[1] << ")" << std::endl;

            std::vector<double> t_virtuel(2); // coordonnées de l'émetteur virtuel
            t_virtuel[0] = t[0] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[0];
            t_virtuel[1] = t[1] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[1];
            std::vector<double> t_virtuel_rel(2); // coordonnées de l'émetteur virtuel par rapport au mur
            t_virtuel_rel[0] = t_rel[0] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[0];
            t_virtuel_rel[1] = t_rel[1] - 2 * dotproduct(t_rel, layout[i].getN()) * layout[i].getN()[1];

            //std::cout << "t_virtuel " << i + 1 << ": (" << t_virtuel[0] << ", " << t_virtuel[1] << ")" << std::endl;

            //std::vector<double> r_copy = r; // copie de r pour la récursion qui peut être modifiée par l'itération suivante
                
            if (rec_depth > 1) {
                compute_reflections(f, layout, i, t_virtuel, r, rec_depth - 1, d, rays_in_scope); // récursion
            } else {
                Ray new_ray(r);
                rays_in_scope.push_back(new_ray); // très important de mettre cette commande après le changement de new_ray, sinon la copie pas modifiée est fournie à la suite
                //std::cout << "this is a new ray" << std::endl; new_ray.print_path();
            }

            std::cout << "rays_in_scope size: " << rays_in_scope.size() << std::endl;

            for (int j = 0; j < rays_in_scope.size(); j++) { // traiter chaque rayon qui arrive au mur individuellement

                std::cout << "this is ray " << j << std::endl;

                std::vector<double> r_copy = rays_in_scope[j].get_last_point(); // copie de r pour la récursion qui peut être modifiée par l'itération suivante

                std::vector<double> r_copy_rel(2); // coordonnées de r par rapport au mur
                r_copy_rel[0] = - layout[i].getU()[0] + r_copy[0];  // vecteur de r à u
                r_copy_rel[1] = - layout[i].getU()[1] + r_copy[1];

                //std::cout << "r_copy: (" << r_copy[0] << ", " << r_copy[1] << ")" << std::endl;

                std::vector<double> diff(2); diff[0] = r_copy[0] - t_virtuel[0]; diff[1] = r_copy[1] - t_virtuel[1];
                double dist = (diff[1] * (r_copy[0] - layout[i].getU()[0]) - diff[0] * (r_copy[1] - layout[i].getU()[1])) / (layout[i].getW()[0] * diff[1] - layout[i].getW()[1] * diff[0]);
                                                                                                                // division par 0 ssi rayon parallèle au mur

                std::cout << "dist: " << dist << std::endl;
                std::cout << "produit de dotproduct: " << dotproduct(t_virtuel, layout[i].getN()) * dotproduct(r_copy, layout[i].getN()) << std::endl;

                if (0.0 < dist && dist < 1.0 // sinon la réflexion est invalide car en dehors du mur -> pas besoin de calculer plus de choses
                            && dotproduct(t_virtuel_rel, layout[i].getN()) * dotproduct(r_copy_rel, layout[i].getN()) < 0.0) { 
                            // si l'antenne virtuelle est du côté opposé au récepteur -> réflexion

                    std::vector<double> r_copy_2 = r_copy; // point de réflexion de l'itération précédente
                    r_copy[0] = layout[i].getU()[0] + dist * layout[i].getW()[0]; // calculer le point de réflexion de cette itération-ci
                    r_copy[1] = layout[i].getU()[1] + dist * layout[i].getW()[1];

                    std::cout << "r_copy: (" << r_copy[0] << ", " << r_copy[1] << ")" << std::endl;
                    std::cout << "r_copy_2: (" << r_copy_2[0] << ", " << r_copy_2[1] << ")" << std::endl;

                    std::vector<double> ray_segment(2); ray_segment[0] = r_copy_2[0] - r_copy[0]; ray_segment[1] = r_copy_2[1] - r_copy[1];

                    rays_in_scope[j].extend_path(r_copy);
                    rays_in_scope[j].add_loss_factor(layout[i].getRcoef(normalised_dotproduct(ray_segment, layout[i].getN())));
                }

                    // calculer la somme de puissance ici -> laisser une méthode de Wall donner les coefs de réflexion et de transmission?

                else { // rebond invalide -> retirer le rayon de la liste des rayons à traiter
                    rays_in_scope.erase(rays_in_scope.begin() + j);
                    j--; // pour ne pas sauter un rayon puisque a liste est réduite de 1 après délétion
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
 }
