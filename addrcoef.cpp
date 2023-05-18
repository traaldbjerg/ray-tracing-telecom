#include "addrcoef.hpp"

void add_Rcoefs(Ray &ray, std::vector<Wall> &layout) { // rajoute tous les facteurs de perte dûs au réflexions dans la liste des pertes du rayon
    std::vector<int> walls_hit = ray.get_walls_hit();
    for (int i = 1; i < walls_hit.size() - 1; i++) {
        std::vector<double> ray_segment = {ray.get_path()[i][0] - ray.get_path()[i-1][0], ray.get_path()[i][1] - ray.get_path()[i-1][1]};
        //std::cout << "wall hit: " << walls_hit[i] << std::endl; // debug
        ray.add_loss_factor(layout[walls_hit[i]].getRcoef(normalised_dotproduct(ray_segment, layout[walls_hit[i]].getN())));
        //std::cout << "Rcoef: " << layout[walls_hit[i]].getRcoef(normalised_dotproduct(ray_segment, layout[walls_hit[i]].getN())) << std::endl; // debug
    }
}
