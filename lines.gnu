reset
set title "Rayons possibles (max 10 réflexions) pour la disposition simplifiée"
set xlabel "x (m)"
set ylabel "y (m)"
set xrange [-6:12]
set yrange [-2:12]
#set palette defined (0 0 0 0.5, 1 0 0 1, 2 0 0.5 1, 3 0 1 1, 4 0.5 1 0.5, 5 1 1 0,  6 1 0.5 0, 7 1 0 0, 8 0.5 0 0)
#do for [mode in "min"] { # pour des petits pas de discrétisation, permet que la fenêtre soit à la bonne couleur
#                         # mais alors porte pas à la bonne couleur :(
#    eval "set pm3d corners2color ".mode
#    splot "mat/out_umfpack.dat" using 2:1:3 with pm3d
#}
set style lines 1 linecolor rgb "green"
plot 'rays.dat' w lp, 'walls.dat' w lp
#set style lines 1 linecolor rgb "black"
#plot 'walls.dat' w lp