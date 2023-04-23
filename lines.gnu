reset
set title "Rayons possibles (max 2 réflexions) pour la disposition de l'usine"
set xlabel "x (m)"
set ylabel "y (m)"
set nokey
set xrange [-10:110]
set yrange [-75:5]
plot 'rays.dat' w lp, 'walls.dat' w lp
