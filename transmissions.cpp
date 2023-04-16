#include "transmissions.hpp"

void find_transmissions(Ray &ray, std::vector<Wall> &layout) { // cherche les intersections de chaque segment du rayon avec des murs de layout

    //std::vector<std::vector<double>> path = ray.get_path(); // récupère le chemin du rayon
    //std::vector<double> last_point = ray.get_last_point(); // récupère le dernier point du rayon
    //std::vector<int> wall_hit = ray.get_walls_hit(); // récupère les murs déjà touchés par le rayon

    //for (int i = 0; i < layout.size(); i++) { // pour chaque mur de layout
        //if (std::find(wall_hit.begin(), wall_hit.end(), i) == wall_hit.end()) { // si le mur n'a pas déjà été touché par le rayon
            //std::vector<double> intersection = find_intersection(path.back(), last_point, layout[i]); // cherche l'intersection entre le segment et le mur
            //if (intersection.size() != 0) { // si l'intersection existe
                //ray.add_wall_hit(i); // ajoute le mur à la liste des murs touchés par le rayon
                //ray.extend_path(intersection); // ajoute l'intersection au chemin du rayon
                //ray.add_loss_factor(layout[i].getTcoef()); // ajoute le facteur de perte du mur au rayon
                //find_transmissions(ray, layout); // relance la fonction sur le rayon modifié
            //}
        //}
    //}


    std::vector<std::vector<double>> path = ray.get_path(); // récupère le chemin du rayon
    ray.add_wall_hit(WALL_PLACEHOLDER); // ajoute un mur en placeholder pour le dernier segment du rayon
    std::vector<int> walls_hit = ray.get_walls_hit(); // récupère les murs déjà touchés par le rayon
    for (int segment = 0; segment < path.size() - 1; segment++) { // pour chaque segment du rayon
        for (int i = 0; i < layout.size(); i++) { // pour chaque mur de layout
            if (i != walls_hit[segment] || i != walls_hit[segment + 1]) { // ne pas considérer les murs entre lesquels le segment se reflète
                //std::vector<double> intersection = find_intersection(path[segment], path[segment + 1], layout[i]); // cherche l'intersection entre le segment et le mur
                if (intersect(path[segment], path[segment + 1], layout[i].getU(), layout[i].getV())) { // si l'intersection existe
                    std::vector<double> ray_segment(2); ray_segment[0] = path[segment][0] - path[segment + 1][0]; ray_segment[1] = path[segment][1] - path[segment + 1][1]; // vecteur représentant le segment du rayon
                    ray.add_loss_factor(layout[i].getTcoef(normalised_dotproduct(ray_segment, layout[i].getN()))); // ajoute le facteur de perte du mur au rayon
                    //std::cout << "Intersection avec le mur " << i << ", facteur de perte : " << layout[i].getTcoef(normalised_dotproduct(ray_segment, layout[i].getN())) << std::endl; // debug
                }
            }
        }
    }
}