reset
set title "Rayons possibles (max 10 réflexions) pour la disposition simplifiée"
set xlabel "x (m)"
set ylabel "y (m)"
set xrange [-6:12]
set yrange [-2:12]
#set style lines 1 linecolor rgb "green"
plot 'rays.dat' w lp, 'walls.dat' w lp
