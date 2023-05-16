reset
set pm3d explicit
set pm3d map
set title "Somme des puissances reçue par un récepteur dans l'usine (dBm)"
set xlabel "x (m)"
set ylabel "y (m)"
set zlabel "Exposition"
set nokey
set xrange [-10:105]
set yrange [-80:5]
set zrange [1:0]
set palette model RGB defined (0 "green",1 "green",1 "red" ,2 "red")
#do for [mode in "min"] { # pour des petits pas de discrétisation, permet que la fenêtre soit à la bonne couleur
                         # mais alors porte pas à la bonne couleur :(
    #eval "set pm3d corners2color ".mode
    splot "danger.dat" using 1:2:3 with pm3d, "walls.dat" using 1:2:(1) w lines
#}
