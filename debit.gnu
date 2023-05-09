reset
set pm3d explicit
set pm3d map
set title "Débit binaire dans l'usine (Mb/s)"
set xlabel "x (m)"
set ylabel "y (m)"
set zlabel "Mb/s"
set nokey
set xrange [-10:105]
set yrange [-80:5]
set zrange [50:350]
set palette defined (0 0 0 0.5, 1 0 0 1, 2 0 0.5 1, 3 0 1 1, 4 0.5 1 0.5, 5 1 1 0,  6 1 0.5 0, 7 1 0 0, 8 0.5 0 0)
#do for [mode in "min"] { # pour des petits pas de discrétisation, permet que la fenêtre soit à la bonne couleur
                         # mais alors porte pas à la bonne couleur :(
    #eval "set pm3d corners2color ".mode
    splot "debit.dat" using 1:2:3 with pm3d, "walls.dat" using 1:2:(70) w lines
#}