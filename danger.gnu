reset
set pm3d explicit
set pm3d map
set title "Respect des normes d'exposition bruxelloises dans l'usine"
set xlabel "x (m)"
set ylabel "y (m)"
set zlabel "Exposition"
set nokey
set xrange [-10:105]
set yrange [-80:5]
set zrange [1:0]
set palette model RGB defined (0 "green",1 "green",1 "red" ,2 "red")
splot "danger.dat" using 1:2:3 with pm3d, "walls.dat" using 1:2:(1) w lines

