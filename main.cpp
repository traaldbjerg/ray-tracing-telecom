#include <iostream>
#include <chrono>
#include <cmath>
#include <complex>
#include <algorithm>
#include "common.hpp"
#include "reflections.hpp"
#include "transmissions.hpp"
#include "time.hpp"
#include "rcoef.hpp"
#include "distance.hpp"
#include "setup.hpp"
#include "antenna.hpp"

int main() {

    // std::cout << "hello this is main" << std::endl; // debug

    // paramètres d'exécution du programme

    const int compute_power = 1; // 1 pour le processus sur toute la zone de la pièce, 0 pour le tracé des rayons
    const int recursion_depth = 2; // nombre de fois qu'on effectue la récursion

    //double frequency = 2.4e9; // fréquence de la porteuse en Hz


    // paramètres de la pièce pour l'exo 8.1
    //std::vector<double> t(2); t[0] = 32 ; t[1] = 10; // coordonnées de l'émetteur
    //std::vector<double> r(2); r[0] = 47; r[1] = 65; // coordonnées du récepteur
    // coordonnées pour l'usine (à changer au besoin)

    std::vector<double> t; // coordonnées de l'émetteur

    //std::vector<double> t(2); t[0] = -10; t[1] = 0.5; // coordonnées de l'émetteur
    std::vector<double> r(2); r[0] = 5; r[1] = -5; // coordonnées du récepteur
    
    std::vector<Antenna> antennas; // vecteur qui contient toutes les antennes
    std::vector<Wall> layout; // vecteur qui contiendra l'ensemble des murs
    std::vector<Ray> rays;    // vecteur qui contiendra l'ensemble des rayons

    // initialiser layout
    //layout.emplace_back(0.0, 0.0, 10.0, 0.0, 2);
    //layout.emplace_back(0.0, 0.0, 0.0, 10.0, 2);
    //layout.emplace_back(0.0, 10.0, 10.0, 10.0, 2);
    //layout.emplace_back(10.0, 0.0, 10.0, 10.0, 2);
    // disposition de l'exo 8.1
    //const Wall wall1(0.0, 0.0, 0.0, 80.0, 4); layout.push_back(wall1);
    //const Wall wall2(0.0, 20.0, 80.0, 20.0, 4); layout.push_back(wall2);
    //const Wall wall3(0.0, 80.0, 80.0, 80.0, 4); layout.push_back(wall3);
    // disposition à 4 murs
    //const Wall wall1(0.0, 0.0, 0.0, 10.0, 2); layout.push_back(wall1); 
    //const Wall wall2(0.0, 0.0, 10.0, 0.0, 2); layout.push_back(wall2);
    //const Wall wall3(0.0, 10.0, 10.0, 10.0, 2); layout.push_back(wall3);
    //const Wall wall4(10.0, 0.0, 10.0, 10.0, 2); layout.push_back(wall4);
    //const Wall wall5(4, 3, 6, 5, 2); layout.push_back(wall5);
    //const Wall wall6(4, 3, 6, 9, 2); layout.push_back(wall6);
    //const Wall wall7(4, 3, 6, 1, 2); layout.push_back(wall7);
    // layout de l'usine
    // murs en brique
    const Wall wall1(0, 0, 100, 0, 1); layout.push_back(wall1);
    const Wall wall2(0, 0, 0, -45, 1); layout.push_back(wall2);
    const Wall wall3(100, 0, 100, -70, 1); layout.push_back(wall3);
    const Wall wall4(85, 0, 85, -12.8398, 1); layout.push_back(wall4);
    const Wall wall5(85, -14.8398, 85, -27.6795, 1); layout.push_back(wall5);
    const Wall wall6(85, -27.6795, 91.5, -27.6795, 1); layout.push_back(wall6);
    const Wall wall7(93.5, -27.6795, 100, -27.6795, 1); layout.push_back(wall7);
    const Wall wall8(85, -27.6795, 75, -45, 1); layout.push_back(wall8);
    // murs en béton
    const Wall wall9(0, -45, 75, -45, 2); layout.push_back(wall9);
    const Wall wall10(75, -45, 75, -70, 2); layout.push_back(wall10);
    const Wall wall11(75, -70, 100, -70, 2); layout.push_back(wall11);
    // cloisons
    const Wall wall12(0, -9, 15, -9, 3); layout.push_back(wall12);
    const Wall wall13(0, -18, 15, -18, 3); layout.push_back(wall13);
    const Wall wall14(0, -27, 15, -27, 3); layout.push_back(wall14);
    const Wall wall15(0, -36, 15, -36, 3); layout.push_back(wall15);
    const Wall wall16(15, 0, 15, -4, 3); layout.push_back(wall16);
    const Wall wall17(15, -5, 15, -13, 3); layout.push_back(wall17);
    const Wall wall18(15, -14, 15, -22, 3); layout.push_back(wall18);
    const Wall wall19(15, -23, 15, -31, 3); layout.push_back(wall19);
    const Wall wall20(15, -32, 15, -40, 3); layout.push_back(wall20);
    const Wall wall21(15, -41, 15, -45, 3); layout.push_back(wall21);
    const Wall wall22(40, -15, 35, -20, 3); layout.push_back(wall22);
    const Wall wall23(35, -30, 40, -35, 3); layout.push_back(wall23);
    const Wall wall24(50, -15, 55, -20, 3); layout.push_back(wall24);
    const Wall wall25(55, -30, 50, -35, 3); layout.push_back(wall25);

    // antennes
    Antenna antenna_1({-10, 0.5}, 3); antennas.push_back(antenna_1); // antenne émettrice

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


        FILE *f_rays = fopen("rays.dat", "w");

        double power = 0; // puissance reçue par le récepteur

        int k = recursion_depth; // debug

        for (int k = 1; k <= recursion_depth; k++) { // d'abord max de réflexions puis ... puis 1 interaction puis 0
            compute_reflections(layout, WALL_PLACEHOLDER, t, r, k, rays); // WALL_PLACEHOLDER défini dans common.hpp
        }

        Ray direct_ray(r); // créer le rayon direct (l'émetteur est rajouté en-dessous dans la boucle for)
        rays.push_back(direct_ray); // rajouter le rayon direct

        for (int i = 0; i < rays.size(); i++) { // pour chaque rayon (il ne reste que les rayons valides à la fin de compute_reflections)
            rays[i].extend_path(t);             // rajouter l'émetteur à la liste des points du rayon
            rays[i].print_path_to_file(f_rays); // écrire le rayon dans le fichier
            //rays[i].print_walls_hit();          // debug
            find_transmissions(rays[i], layout); // trouver les transmissions
            compute_distance(rays[i]); // calculer la distance parcourue par le rayon
            add_Rcoefs(rays[i], layout); // ajouter les coefficients de réflexion
            rays[i].print_path();               // debug
            rays[i].print_loss_factors();       // debug
            //printf("Power of ray %d is %e\n", i, rays[i].compute_power()); // debug
            power += abs(rays[i].compute_field()) * abs(rays[i].compute_field());   // calculer la puissance reçue par le récepteur
        }
        
        fclose(f_rays);
        power *= G_TX * P_TX * 60 * 32 * (CELERITY / FREQUENCY) * (CELERITY / FREQUENCY) / (M_PI * M_PI * 8 * 720 * M_PI);
        system("gnuplot -persist \"lines.gnu\""); // afficher les rayons
        std::cout << "Power is " << 10 * log10(power* 1000) << " dBm" << std::endl;
    }

    // boucle pour l'entièreté de la grille, calculer la puissance

    if (compute_power == 1) {

        const double h = 5; // nombre de pas par mètre
        const double Lx = 100.0;
        const double Ly = 70.0;

        double power;
        //std::complex<double> field(0.0, 0.0);
        double field_modulus;

        double progress_save = -1; // -1 pour être sûr que la barre est affichée immédiatement

        std::vector<double> power_list(antennas.size()); // liste des puissances de chaque antenne reçue par le récepteur

        FILE *f_power = fopen("power.dat", "w");
        // boucle pour toutes les positions de récepteur, plotter la puissance sur une grille
        for (int i = 0; i <= Lx * h; i++) { // itère d'abord verticalement, colonne par colonne
            r[0] = i/h;
            for(int j = 0 ; j < Ly * h ; j++) {
                r[1] = -j/h;

                if (!(r[1] < -45 && r[0] < 75)) {  // si le récepteur est dans la pièce, on calcule la puissance

                    for (int q = 0; q < antennas.size(); q++) {

                        int k = recursion_depth; // debug
                    
                        power = 0;
                        //field = 0.0;
                        for (int k = 1; k <= recursion_depth; k++) { // d'abord max de réflexions puis ... puis 1 interaction puis 0
                            compute_reflections(layout, WALL_PLACEHOLDER, antennas[q].get_position(), r, k, rays); // WALL_PLACEHOLDER défini dans common.hpp
                        }

                        if ((double (i / (Lx*h))) > (progress_save + 0.005)) { // pour ne pas faire du in/out (très lent) quand le résultat n'a pas changé
                            progress_save = double (i / (Lx*h));
                            printProgress(progress_save); // afficher l'avancement de la boucle
                        }
    
                        Ray direct_ray(r); // créer le rayon direct (l'émetteur est rajouté en-dessous dans la boucle for)
                        rays.push_back(direct_ray); // rajouter le rayon direct
                        for (int l = 0; l < rays.size(); l++) { // pour chaque rayon (il ne reste que les rayons valides à la fin de compute_reflections)
                            rays[l].extend_path(antennas[q].get_position());             // rajouter l'émetteur à la liste des points du rayon
                            //rays[l].print_path();               // debug
                            //rays[l].print_loss_factors();       // debug
                            //rays[l].print_path_to_file(f_rays); // écrire le rayon dans le fichier
                            find_transmissions(rays[l], layout); // trouver les transmissions
                            compute_distance(rays[l]); // calculer la distance parcourue par le rayon
                            add_Rcoefs(rays[l], layout); // ajouter les coefficients de réflexion
                            rays[l].add_loss_factor(antennas[q].compute_directivity(acos(normalised_dotproduct(rays[l].get_last_segment(), {1, 0})))); // ajouter le gain de directivité
                            //field += rays[l].compute_field(); // calculer le champ, METHODE NON MOYENNEE
                            field_modulus = abs(rays[l].compute_field()); // calculer le champ, METHODE MOYENNEE
                            power += field_modulus * field_modulus; // calculer la puissance, FORMULE DE MOYENNE 8.80 ET PAS 8.79
                        }
                        //std::cout << "Point : (" << r[0] << ", " << r[1] << ") ; number of rays : " << rays.size() << std::endl; // debug
                        rays.clear(); // vider le vecteur de rayons pour la prochaine itération (sinon le vecteur devient énorme et le programme plante)
                        //power = real(field * conj(field)); // calculer la puissance
                        power *= antennas[q].get_G_TX() * antennas[q].get_P_TX() * 60 * 32 * (CELERITY / FREQUENCY) * (CELERITY / FREQUENCY) / (M_PI * M_PI * 8 * 720 * M_PI); // rajouter les facteurs multiplicatifs, 720 pi /32 est R_a
                        power_list[q] = power; // ajouter la puissance à la liste des puissances reçues par le point
                    }
                    double max_power = *std::max_element(std::begin(power_list), std::end(power_list)); // trouver la puissance maximale reçue par le point
                    fprintf(f_power, "%f %f %f\n", r[0], r[1], std::min(-60.0, 10 * log10(max_power * 1000)));
                    power_list.clear(); // retirer les différentes puissances reçues par le point
                }
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
