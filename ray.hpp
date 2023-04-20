#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <complex>

class Ray {
    // classe rayon, reprend les propriétés des rayons (extrémités des segments, facteurs de perte)

    // attributs
    private:
        std::vector<std::vector<double>> path;
        std::vector<std::complex<double>> loss_factors;
        std::vector<int> walls_hit;
    
    // méthodes
    public:
        Ray(std::vector<double> r); // constructeur
        ~Ray(); // destructeur
        void add_loss_factor(std::complex<double> factor); // rajouter un facteur de perte dans la liste
        void add_loss_factor(double factor);
        //void add_all_loss_factors(std::vector<Wall> &layout); // rajoute tous les facteurs de perte d'un vecteur dans la liste des facteurs de perte du rayon
        std::complex<double> compute_field(); // calcule le facteur de perte total du rayon
        void add_wall_hit(int wall_index); // rajoute un mur dans la liste des murs touchés
        std::vector<int> get_walls_hit(); // retourne la liste des murs touchés par le rayon
        std::vector<double> get_last_point(); // retourne le dernier point du rayon
        void extend_path(std::vector<double> new_point); // rajoute un point à la liste des points du rayon
        std::vector<std::vector<double>> get_path(); // retourne l'ensemble des extrémités des segments du rayon
        void print_path(); // debug
        void print_path_to_file(FILE *f); // écrit l'ensemble des extrémités des segments du rayon dans le fichier f, pour plotter avec gnuplot
        void print_loss_factors(); // debug
        void print_walls_hit(); // debug
};
