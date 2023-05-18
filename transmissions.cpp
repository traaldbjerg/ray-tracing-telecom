#include "transmissions.hpp"

void find_transmissions(Ray &ray, std::vector<Wall> &layout) { // cherche les intersections de chaque segment du rayon avec des murs de layout

    std::vector<std::vector<double>> path = ray.get_path(); // récupère le chemin du rayon
    ray.add_wall_hit(WALL_PLACEHOLDER); // ajoute un mur en placeholder pour le dernier segment du rayon
    std::vector<int> walls_hit = ray.get_walls_hit(); // récupère les murs déjà touchés par le rayon
    for (int segment = 0; segment < path.size() - 1; segment++) { // pour chaque segment du rayon
        for (int i = 0; i < layout.size(); i++) { // pour chaque mur de layout
            if (i != walls_hit[segment] && i != walls_hit[segment + 1]) { // ne pas considérer les murs entre lesquels le segment se reflète
                if (intersect(path[segment], path[segment + 1], layout[i].getU(), layout[i].getV())) { // si l'intersection existe
                    std::vector<double> ray_segment(2); ray_segment[0] = path[segment][0] - path[segment + 1][0]; ray_segment[1] = path[segment][1] - path[segment + 1][1]; // vecteur représentant le segment du rayon
                    ray.add_loss_factor(layout[i].getTcoef(normalised_dotproduct(ray_segment, layout[i].getN()))); // ajoute le facteur de perte du mur au rayon
                }
            }
        }
    }
}