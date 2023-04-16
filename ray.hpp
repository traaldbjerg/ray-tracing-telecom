#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

class Ray {
    // classe rayon, reprend les propriétés des rayons (extrémités des segments, facteurs de perte)

    // attributs
    private:
        std::vector<std::vector<double>> path;
        std::vector<double> loss_factors;
    
    // méthodes
    public:
        Ray(std::vector<double> r); // constructeur
        ~Ray(); // destructeur
        void add_loss_factor(double factor); // rajouter un facteur de perte dans la liste
        double compute_power(); // calcule le facteur de perte total du rayon
        std::vector<double> get_last_point(); // retourne le dernier point du rayon
        void extend_path(std::vector<double> new_point); // rajoute un point à la liste des points du rayon
        std::vector<std::vector<double>> get_path(); // retourne l'ensemble des extrémités des segments du rayon
        void print_path(); // debug
        void print_path_to_file(FILE *f); // écrit l'ensemble des extrémités des segments du rayon dans le fichier f, pour plotter avec gnuplot
        void print_loss_factors(); // debug
};
