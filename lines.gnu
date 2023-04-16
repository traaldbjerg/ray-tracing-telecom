reset
set title "Rayons possibles (max 4 réflexions) pour la disposition de l'usine"
set xlabel "x (m)"
set ylabel "y (m)"
set xrange [-10:105]
set yrange [-80:5]
plot 'rays.dat' w lp, 'walls.dat' w lp
