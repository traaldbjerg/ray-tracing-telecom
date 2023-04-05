reset
set pm3d map
set title "Distribution de température dans la pièce numéro 23, solution par UMFPACK (°C)"
set xlabel "x (m)"
set ylabel "y (m)"
set zlabel "T (°C)"
set xrange [0.0:5.50]
set yrange [0.0:5.50]
set zrange [0.0:50.0]
set palette defined (0 0 0 0.5, 1 0 0 1, 2 0 0.5 1, 3 0 1 1, 4 0.5 1 0.5, 5 1 1 0,  6 1 0.5 0, 7 1 0 0, 8 0.5 0 0)
do for [mode in "min"] { # pour des petits pas de discrétisation, permet que la fenêtre soit à la bonne couleur
                         # mais alors porte pas à la bonne couleur :(
    eval "set pm3d corners2color ".mode
    splot "mat/out_umfpack.dat" using 2:1:3 with pm3d
}
