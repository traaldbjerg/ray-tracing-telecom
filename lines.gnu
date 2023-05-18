reset
set title "Rayons possibles (max 9 réflexions) pour une disposition carrée"
set xlabel "x (m)"
set ylabel "y (m)"
set nokey
set xrange [-10:15]
set yrange [-5:15]
plot 'rays.dat' w lp, 'walls.dat' w lp
