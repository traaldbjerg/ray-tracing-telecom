#include <iostream>
#include <chrono>
#include <cmath>
#include "common.hpp"
#include "reflections.hpp"
#include "transmissions.hpp"
#include "time.hpp"

int main()
{

    // std::cout << "hello this is main" << std::endl; // debug

    // paramètres d'exécution du programme

    const int compute_power = 1; // 1 pour le processus sur toute la zone de la pièce, 0 pour le tracé des rayons
    const int recursion_depth = 4; // nombre de fois qu'on effectue la récursion


    // variables à fixer

    const double h = 10; // nombre de pas par mètre
    const double Lx = 10.0;
    const double Ly = 10.0;
    double power = 0.0;

    // std::vector<double> t(2); t[0] = 32 ; t[1] = 10; // coordonnées de l'émetteur
    // std::vector<double> r(2); r[0] = 47; r[1] = 65; // coordonnées du récepteur
    std::vector<double> t(2); t[0] = -5; t[1] = 5; // coordonnées de l'émetteur
    std::vector<double> r(2);
    
    std::vector<Wall> layout; // vecteur qui contiendra l'ensemble des murs
    std::vector<Ray> rays;    // vecteur qui contiendra l'ensemble des rayons

    // initialiser layout
    // layout.emplace_back(0.0, 0.0, 10.0, 0.0, 2);
    // layout.emplace_back(0.0, 0.0, 0.0, 10.0, 2);
    // layout.emplace_back(0.0, 10.0, 10.0, 10.0, 2);
    // layout.emplace_back(10.0, 0.0, 10.0, 10.0, 2);
    // disposition de l'exo 8.1
    // Wall wall1(0.0, 0.0, 0.0, 80.0, 2); layout.push_back(wall1);
    // Wall wall2(0.0, 20.0, 80.0, 20.0, 2); layout.push_back(wall2);
    // Wall wall3(0.0, 80.0, 80.0, 80.0, 2); layout.push_back(wall3);
    // disposition à 4 murs
    const Wall wall1(0.0, 0.0, 0.0, 10.0, 2); layout.push_back(wall1);
    const Wall wall2(0.0, 0.0, 10.0, 0.0, 2); layout.push_back(wall2);
    const Wall wall3(0.0, 10.0, 10.0, 10.0, 2); layout.push_back(wall3);
    const Wall wall4(10.0, 0.0, 10.0, 10.0, 2); layout.push_back(wall4);
    const Wall wall5(4, 3, 6, 5, 2); layout.push_back(wall5);
    const Wall wall6(4, 3, 6, 9, 2); layout.push_back(wall6);
    const Wall wall7(4, 3, 6, 1, 2); layout.push_back(wall7);

    // int q = layout.size(); // nombre de murs

    // placer les murs dans le fichier correspondant

    FILE *f_walls = fopen("walls.dat", "w");
    for (int i = 0; i < layout.size(); i++) {
        layout[i].print_wall_to_file(f_walls);
    }
    fclose(f_walls);

    const double tc5 = mytimer_cpu(); const double tw5 = mytimer_wall(); // mesurer le temps d'exécution

    // fonctions à appeler

    // boucle pour un récepteur unique, tracer les rayons

    if (compute_power == 0) {

        r[0] = 5; r[1] = 5; // coordonnées du récepteur

        FILE *f_rays = fopen("rays.dat", "w");

        for (int k = 1; k <= recursion_depth; k++) { // d'abord max de réflexions puis ... puis 1 interaction puis 0
            compute_reflections(layout, WALL_PLACEHOLDER, t, r, k, rays); // WALL_PLACEHOLDER défini dans common.hpp
        }

        Ray direct_ray(r); // créer le rayon direct (l'émetteur est rajouté en-dessous dans la boucle for)
        rays.push_back(direct_ray); // rajouter le rayon direct

        for (int i = 0; i < rays.size(); i++) { // pour chaque rayon (il ne reste que les rayons valides à la fin de compute_reflections)
            rays[i].extend_path(t);             // rajouter l'émetteur à la liste des points du rayon
            //rays[i].print_path();               // debug
            //rays[i].print_loss_factors();       // debug
            rays[i].print_path_to_file(f_rays); // écrire le rayon dans le fichier
            //rays[i].print_walls_hit();          // debug
            find_transmissions(rays[i], layout); // trouver les transmissions
            //printf("Power of ray %d is %e\n", i, rays[i].compute_power()); // debug
        }

        fclose(f_rays);

        system("gnuplot -persist \"lines.gnu\""); // afficher les rayons

    }

    // boucle pour l'entièreté de la grille, calculer la puissance

    if (compute_power == 1) {

        double progress_save = -1; // -1 pour être sûr que la barre est affichée immédiatement

        FILE *f_power = fopen("power.dat", "w");
        // boucle pour toutes les positions de récepteur, plotter la puissance sur une grille
        for (int i = 0; i <= Lx * h; i++) { // itère d'abord verticalement, colonne par colonne
            r[0] = i/h;
            for(int j = 0 ; j < Ly * h ; j++) {
                r[1] = j/h;
                
                power = 0;
                for (int k = 1; k <= recursion_depth; k++) { // d'abord max de réflexions puis ... puis 1 interaction puis 0
                    compute_reflections(layout, WALL_PLACEHOLDER, t, r, k, rays); // WALL_PLACEHOLDER défini dans common.hpp
                }

                if ((double (i / (Lx*h))) > (progress_save + 0.005)) { // pour ne pas faire du in/out (très lent) quand le résultat n'a pas changé
                    progress_save = double (i / (Lx*h));
                    printProgress(progress_save); // afficher l'avancement de la boucle
                }

                Ray direct_ray(r); // créer le rayon direct (l'émetteur est rajouté en-dessous dans la boucle for)
                rays.push_back(direct_ray); // rajouter le rayon direct

                for (int l = 0; l < rays.size(); l++) { // pour chaque rayon (il ne reste que les rayons valides à la fin de compute_reflections)
                    rays[l].extend_path(t);             // rajouter l'émetteur à la liste des points du rayon
                    //rays[l].print_path();               // debug
                    //rays[l].print_loss_factors();       // debug
                    //rays[l].print_path_to_file(f_rays); // écrire le rayon dans le fichier
                    //find_transmissions(rays[l], layout); // trouver les transmissions
                    power += rays[l].compute_power();
                }
                rays.clear(); // vider le vecteur de rayons pour la prochaine itération (sinon le vecteur devient énorme et le programme plante)
                fprintf(f_power, "%f %f %f\n", r[0], r[1], power);
            }
            fprintf(f_power, "\n"); // pour respecter le format gnuplot
        }
        
        fclose(f_power);

        system("gnuplot -persist \"heatmap.gnu\""); // afficher la puissance sur une grille

    }

    double tc6 = mytimer_cpu(); double tw6 = mytimer_wall();

    // mesurer le temps d'exécution

    std::cout << std::endl; // rajouter une ligne après la barre de progresion

    std::cout << "CPU time: " << tc6 - tc5 << " s" << std::endl;
    std::cout << "Clock time: " << tw6 - tw5 << " s" << std::endl;

}
