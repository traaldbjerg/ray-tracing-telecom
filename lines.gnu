reset
set title "Rayons possibles (max 4 réflexions) pour la disposition de l'usine"
set xlabel "x (m)"
set ylabel "y (m)"
set nokey
set xrange [-10:85]
set yrange [-5:85]
plot 'rays.dat' w lp, 'walls.dat' w lp
